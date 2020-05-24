#include "game.h"
#include <iostream>
#include "SDL.h"
#include "snake_body.h"
namespace snake {

    Game::Game(std::size_t grid_width,
            std::size_t grid_height)
            : snake(grid_width, grid_height) {
        random2DGenerator = std::make_unique<Random2DGenerator>(grid_width,
                                                                grid_height);
        WaitPlaceFood();
    }

    void Game::Run(Controller const &controller, Renderer &renderer,
                   std::size_t target_frame_duration) {
        Uint32 title_timestamp = SDL_GetTicks();
        Uint32 frame_start;
        Uint32 frame_end;
        Uint32 frame_duration;
        int frame_count = 0;
        bool running = true;

        while (running) {
            frame_start = SDL_GetTicks();

            // Input, Update, Render - the main game loop.
            controller.HandleInput(running, snake);
            Update();
            const Snake_Point snakeFoodPoint = Point(food.x, food.y);

            renderer.Render(snake, snakeFoodPoint);

            frame_end = SDL_GetTicks();

            // Keep track of how long each loop through the input/generate2DValues/render cycle
            // takes.
            frame_count++;
            frame_duration = frame_end - frame_start;

            // After every second, generate2DValues the window title.
            if (frame_end - title_timestamp >= 1000) {
                renderer.UpdateWindowTitle(score, frame_count);
                frame_count = 0;
                title_timestamp = frame_end;
            }

            // If the time for this frame is too small (i.e. frame_duration is
            // smaller than the target ms_per_frame), delay the loop to
            // achieve the correct frame rate.
            if (frame_duration < target_frame_duration) {
                SDL_Delay(target_frame_duration - frame_duration);
            }
        }
    }

    void Game::WaitPlaceFood() {
        std::lock_guard<std::mutex> lockGuard(_mutex);
        std::cout << "Placing food" << std::endl;

        while (true) {
            random2DGenerator->generate2DValues();
            int x = random2DGenerator->GetX();
            int y = random2DGenerator->GetY();
            if (!snake.SnakeCell(x, y)) {
                food.x = x;
                food.y = y;
                std::cout << "Food placed at coords:" << x << ", " << y << std::endl;
                break;
            }
        }
        _condition.notify_one();
    }

    void Game::Update() {
        if (!snake.alive) return;

        snake.Update();

        int new_x = static_cast<int>(snake.head_x);
        int new_y = static_cast<int>(snake.head_y);

        // Check if there's food over here
        if (food.x == new_x && food.y == new_y) {
            score++;
            WaitPlaceFood();
            // Grow snake and increase speed.
            snake.GrowBody();
            snake.speed += 0.02;
        }
    }

    int Game::GetScore() const { return score; }

    int Game::GetSize() const { return snake.size; }
}