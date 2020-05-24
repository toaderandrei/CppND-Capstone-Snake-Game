//
// Created by toaderst on 24-05-20.
//

#ifndef SDL2TEST_SNAKE_BODY_H
#define SDL2TEST_SNAKE_BODY_H
typedef struct Point {
    int x;
    int y;

    Point(int _x, int _y) : x(_x), y(_y) {}
} Snake_Point;

#endif //SDL2TEST_SNAKE_BODY_H
