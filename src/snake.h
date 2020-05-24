#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"
#include <memory>
#include <deque>
#include <mutex>
#include <condition_variable>
#include <stack>
#include "snake_body.h"
#include "board.h"

namespace snake {

    template<class T>
    class SyncQueue {
    public:
        // constructors/destructors
        SyncQueue();

        ~SyncQueue();

        // other public methods.

        T remove();

        void add(const T &msg);

        std::deque<T> elements();

    private:
        std::deque<T> _queue;
        std::condition_variable _condition_variable;
        std::mutex _mutex_queue;
    };


    class Snake {
    public:
        enum class Direction {
            kUp, kDown, kLeft, kRight
        };

        Snake(const Board &_board);

        void Update();

        void GrowBody();

        bool SnakeCell(const Snake_Cell &cell);

        Direction direction = Direction::kUp;

        float speed{0.1f};
        int size{1};
        bool alive{true};
        float head_x;
        float head_y;

        std::shared_ptr<SyncQueue<Snake_Point>> _sync_queue;

    private:
        void UpdateHead();

        void UpdateBody(const Snake_Point &current_head_cell, const Snake_Point &prev_head_cell);

        bool growing{false};
        Board board;
    };

}

#endif