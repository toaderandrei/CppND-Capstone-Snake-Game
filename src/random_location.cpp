//
// Created by toaderst on 24-05-20.
//

#include "random_location.h"

Random2DGenerator::Random2DGenerator(std::size_t grid_width, std::size_t grid_height) : engine(dev()),
                                                                                        random_w(0,
                                                                                                 static_cast<int>(grid_width)),
                                                                                        random_h(0,
                                                                                                 static_cast<int>(grid_height)) {
}

Random2DGenerator::~Random2DGenerator() {}

void Random2DGenerator::generate2DValues() {
    while (true) {
        x = random_w(engine);
        y = random_h(engine);
        // we check if the values are inside the grid.
        if (x < random_w.b() && y < random_h.b()) {
            return;
        }
    }
}

int Random2DGenerator::GetX() {
    return x;
}

int Random2DGenerator::GetY() {
    return y;
}