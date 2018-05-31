#pragma once

namespace reversi {

    // changing these values will break the game
    enum color {
        unoccupied = 0,
        white =  1,
        black = -1
    };

    // changing these values will break the game
    enum gamestate {
        draw = 0,
        white_turn =  1,
        black_turn = -1,
        white_won  =  2,
        black_won  = -2
    };

    typedef unsigned int score;

    class InvalidMoveException : public std::exception {};

}
