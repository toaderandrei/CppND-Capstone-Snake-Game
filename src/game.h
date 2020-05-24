#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "random_location.h"
#include <memory>
#include <mutex>
#include <condition_variable>

namespace snake {

    class Game {
    public:
        Game(std::size_t grid_width, std::size_t grid_height);

        void Run(Controller const &controller, Renderer &renderer,
                 std::size_t target_frame_duration);

        int GetScore() const;

        int GetSize() const;

    private:
        std::mutex _mutex;
        std::condition_variable _condition;

        //    std::unique_ptr<Snake> snake;
        Snake snake;
        SDL_Point food;

        std::unique_ptr<Random2DGenerator> random2DGenerator;

        int score{0};

        void WaitPlaceFood();

        void Update();
    };
}
#endif