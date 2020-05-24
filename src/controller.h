#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

namespace snake {
    class Controller {
    public:
        void HandleInput(bool &running, snake::Snake &snake) const;

    private:
        void ChangeDirection(snake::Snake &snake, Snake::Direction input,
                             Snake::Direction opposite) const;
    };
}
#endif