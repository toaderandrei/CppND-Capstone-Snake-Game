//
// Created by toaderst on 24-05-20.
//
#include "board.h"

namespace snake {

    Board::Board(std::size_t w, std::size_t h) : board_width(w), board_height(h) {}

    Board::~Board() {}

    std::size_t Board::get_height() const {
        return board_height;
    }

    std::size_t Board::get_width() const {
        return board_width;
    }
}