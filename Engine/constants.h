#pragma once

namespace reversi {

    enum color {
        unoccupied = 0,
        white = 1,
        black = 2
    };

    typedef unsigned int score;

    class InvalidMoveException : public std::exception {};

}
