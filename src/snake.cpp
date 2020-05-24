#include "snake.h"
#include <cmath>
#include <iostream>

namespace snake {


    /* Implementation of class "SyncQueue" */
    template<class T>
    SyncQueue<T>::SyncQueue() {
        std::cout << "Construction of the SyncQueue Object." << std::endl;
    }

    template<class T>
    SyncQueue<T>::~SyncQueue() {
        std::cout << "Destroying the SyncQueue Object." << std::endl;
    }

    template<typename T>
    T SyncQueue<T>::remove() {
        std::lock_guard<std::mutex> lock_guard(_mutex_queue);
        T message = std::move(_queue.back());
        _queue.erase(_queue.begin());
        return message;
    }

    template<typename T>
    void SyncQueue<T>::add(const T &msg) {
        std::lock_guard<std::mutex> lock_guard(_mutex_queue);
        _queue.push_back(msg);
        _condition_variable.notify_one();
    }

    template<typename T>
    std::deque<T> SyncQueue<T>::elements() {
        return _queue;
    }

    Snake::Snake(const Board &_board) : board(_board),
                                        head_x(board.get_width() / 2),
                                        head_y(board.get_height() / 2) {
        _sync_queue = std::make_shared<SyncQueue<Snake_Point>>();
    }

    void Snake::Update() {
        Snake_Point prev_cell{
                static_cast<int>(head_x),
                static_cast<int>(head_y)};  // We first capture the head's cell before updating.

        UpdateHead();

        Snake_Point current_cell{
                static_cast<int>(head_x),
                static_cast<int>(head_y)};  // Capture the head's cell after updating.

        // Update all of the body vector items if the snake_ptr head has moved to a new
        // cell.
        if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
            UpdateBody(current_cell, prev_cell);
        }
    }

    void Snake::UpdateHead() {
        switch (direction) {
            case Direction::kUp:
                head_y -= speed;
                break;

            case Direction::kDown:
                head_y += speed;
                break;

            case Direction::kLeft:
                head_x -= speed;
                break;

            case Direction::kRight:
                head_x += speed;
                break;
        }

        // Wrap the Snake around to the beginning if going off of the screen.
        head_x = fmod(head_x + board.get_width(), board.get_width());
        head_y = fmod(head_y + board.get_height(), board.get_height());
    }

    void Snake::UpdateBody(const Snake_Point &current_head_cell, const Snake_Point &prev_head_cell) {
        // Add previous head location to vector
        _sync_queue->add(prev_head_cell);

        if (!growing) {
            // Remove the tail from the vector.
            _sync_queue->remove();
        } else {
            growing = false;
            size++;
        }

        // Check if the snake_ptr has died.
        for (auto const &item : _sync_queue->elements()) {
            if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
                alive = false;
            }
        }
    }

    // Inefficient method to check if cell is occupied by snake_ptr.
    bool Snake::SnakeCell(const Snake_Cell &cell) {
        if (cell.x == static_cast<int>(head_x) && cell.y == static_cast<int>(head_y)) {
            return true;
        }
        for (auto const &item : _sync_queue->elements()) {
            if (cell.x == item.x && cell.y == item.y) {
                return true;
            }
        }
        return false;
    }

    void Snake::GrowBody() { growing = true; }
}