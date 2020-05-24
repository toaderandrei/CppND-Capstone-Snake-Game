//
// Created by toaderst on 24-05-20.
//

#include <iostream>
#include <random>

#ifndef SDL2TEST_SNAKE_LOCATION_H
#define SDL2TEST_SNAKE_LOCATION_H

#endif //SDL2TEST_SNAKE_LOCATION_H


class Random2DGenerator {
public:

    Random2DGenerator(std::size_t grid_width,
                      std::size_t grid_height);

    ~Random2DGenerator();

    void generate2DValues();

    /**
     * Returns the x location.
     * @return the x location of the food.
     */
    int GetX();

    /**
     * Returns the y location.
     * @return the y location of the food.
     */
    int GetY();

private:
    int x;
    int y;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_w;
    std::uniform_int_distribution<int> random_h;
};