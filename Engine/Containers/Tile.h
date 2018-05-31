#pragma once


#include <string>

namespace reversi {

    typedef unsigned char coordinate;

    class Tile {
    public:
        coordinate x, y;

        Tile();

        Tile(coordinate x, coordinate y);

        Tile(std::string str);

        std::string toString() const;

        // isOnBoard
        // Determines if the supplied position (x/y indexes) is within the game board.
        bool isOnBoard() const;
    };

}
