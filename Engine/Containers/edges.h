#pragma once

#include <vector>
#include "Tile.h"


namespace reversi::edges {
    const std::vector<Tile> TOP    = {Tile(0,0), Tile(1,0), Tile(2,0), Tile(3,0), Tile(4,0), Tile(5,0), Tile(6,0), Tile(7,0)};
    const std::vector<Tile> BOTTOM = {Tile(0,7), Tile(1,7), Tile(2,7), Tile(3,7), Tile(4,7), Tile(5,7), Tile(6,7), Tile(7,7)};
    const std::vector<Tile> LEFT   = {Tile(0,0), Tile(0,1), Tile(0,2), Tile(0,3), Tile(0,4), Tile(0,5), Tile(0,6), Tile(0,7)};
    const std::vector<Tile> RIGHT  = {Tile(7,0), Tile(7,1), Tile(7,2), Tile(7,3), Tile(7,4), Tile(7,5), Tile(7,6), Tile(7,7)};

    const std::vector<Tile> TOP_LEFT     = {Tile(0,0), Tile(1,0), Tile(2,0), Tile(3,0), Tile(4,0), Tile(5,0), Tile(6,0), Tile(7,0),
                                           /* -||- */  Tile(0,1), Tile(0,2), Tile(0,3), Tile(0,4), Tile(0,5), Tile(0,6), Tile(0,7)};
    const std::vector<Tile> TOP_RIGHT    = {Tile(0,0), Tile(1,0), Tile(2,0), Tile(3,0), Tile(4,0), Tile(5,0), Tile(6,0), Tile(7,0),
                                           /* -||- */  Tile(7,1), Tile(7,2), Tile(7,3), Tile(7,4), Tile(7,5), Tile(7,6), Tile(7,7)};
    const std::vector<Tile> BOTTOM_LEFT  = {Tile(0,7), Tile(1,7), Tile(2,7), Tile(3,7), Tile(4,7), Tile(5,7), Tile(6,7), Tile(7,7),
                                            Tile(0,0), Tile(0,1), Tile(0,2), Tile(0,3), Tile(0,4), Tile(0,5), Tile(0,6) /* -||- */};
    const std::vector<Tile> BOTTOM_RIGHT = {Tile(0,7), Tile(1,7), Tile(2,7), Tile(3,7), Tile(4,7), Tile(5,7), Tile(6,7), Tile(7,7),
                                            Tile(7,0), Tile(7,1), Tile(7,2), Tile(7,3), Tile(7,4), Tile(7,5), Tile(7,6) /* -||- */};

    const std::vector<Tile> EDGES[8] = {
            TOP,
            BOTTOM,
            LEFT,
            RIGHT,
            TOP_LEFT,
            BOTTOM_LEFT,
            TOP_RIGHT,
            BOTTOM_RIGHT
    };
}
