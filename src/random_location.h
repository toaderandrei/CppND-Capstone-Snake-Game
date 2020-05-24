//
// Created by toaderst on 24-05-20.
//

#include <iostream>
#include <random>
#include <memory>

#ifndef SDL2TEST_SNAKE_LOCATION_H
#define SDL2TEST_SNAKE_LOCATION_H

#endif //SDL2TEST_SNAKE_LOCATION_H

#include "board.h"
#include "snake_body.h"

class Random2DGenerator {
public:

    Random2DGenerator(const snake::Board &board);

    ~Random2DGenerator();

    void generate2DValues();

    /**
     * Returns the x location.
     * @return the x location of the food.
     */
    Cell GetCell();


private:
    Snake_Cell cell;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};