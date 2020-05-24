#ifndef GAME_H
#define GAME_H

#include <random>
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "random_location.h"
#include <memory>
#include <mutex>
#include <condition_variable>

#include "board.h"

namespace snake {

    class Game {
    public:
        Game(const Board& board);

        void Run(Controller const &controller, Renderer &renderer,
                 std::size_t target_frame_duration);

        int GetScore() const;

        int GetSize() const;

    private:
        std::mutex _mutex;
        std::condition_variable _condition;

        std::unique_ptr<snake::Snake> snake_ptr;
        Snake_Point food;

        std::unique_ptr<Random2DGenerator> random_2d_ptr;

        int score{0};

        void WaitPlaceFood();

        void Update();
    };
}
#endif