//
// Created by toaderst on 24-05-20.
//

#include "random_location.h"

Random2DGenerator::Random2DGenerator(const snake::Board &board) : engine(dev()),
                                                                            random_w(0,
                                                                                     static_cast<int>(board.get_width())),
                                                                            random_h(0,
                                                                                     static_cast<int>(board.get_height())) {
}

Random2DGenerator::~Random2DGenerator() {}

void Random2DGenerator::generate2DValues() {
    while (true) {
        cell.x = random_w(engine);
        cell.y = random_h(engine);
        // we check if the values are inside the grid.
        if (cell.x < random_w.b() && cell.y < random_h.b()) {
            return;
        }
    }
}

Cell Random2DGenerator::GetCell() {
    return cell;
}