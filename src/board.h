//
// Created by toaderst on 24-05-20.
//

#ifndef SDL2TEST_BOARD_H
#define SDL2TEST_BOARD_H

#include <cstdio>

namespace snake {

    class Board {

    public:
        Board(std::size_t w, std::size_t h);

        ~Board();

        [[nodiscard]] std::size_t get_width() const;

        [[nodiscard]] std::size_t get_height() const;
    private:
        std::size_t board_width;
        std::size_t board_height;
    };


}
#endif //SDL2TEST_BOARD_H
