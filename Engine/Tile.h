#pragma once


#include <string>

namespace reversi {

    typedef unsigned char coordinate;

    class Tile {
    public:
        coordinate x, y;

        Tile(coordinate x, coordinate y);

        Tile(std::string str);

        std::string toString() const;
    };

}
