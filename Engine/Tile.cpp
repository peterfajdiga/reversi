#include "Tile.h"

namespace reversi {
    Tile::Tile(coordinate x, coordinate y) : x(x), y(y) {}

    Tile::Tile(std::string str) {
        const char& p0 = str[0];
        const char& p1 = str[1];

        bool isLetterFirst = p0 >= 'a' && p0 <= 'z';  // accept both 'a1' and '1a' as valid moves

        // x index
        // subtract charcode for 'a' from letter character's charcode
        x = tolower((isLetterFirst ? p0 : p1)) - 'a';

        // y index
        // subtract charcode for '1' from number character's charcode
        y = (isLetterFirst ? p1 : p0) - '1';
    }

    std::string Tile::toString() const {
        std::string str;
        str += x + 'a';
        str += y + '1';
        return str;
    }
}
