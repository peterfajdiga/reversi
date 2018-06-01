#include "Tile.h"

namespace reversi {

    Tile::Tile() = default;

    Tile::Tile(coordinate x, coordinate y) : x(x), y(y) {}

    Tile::Tile(std::string str) {
        const char& p0 = str[0];
        const char& p1 = str[1];

        bool isLetterFirst = p0 >= 'a' && p0 <= 'z';  // accept both 'a1' and '1a' as valid moves

        // x index
        // subtract charcode for 'a' from letter character's charcode
        x = (coordinate)(tolower((isLetterFirst ? p0 : p1)) - 'a');

        // y index
        // subtract charcode for '1' from number character's charcode
        y = (coordinate)((isLetterFirst ? p1 : p0) - '1');
    }


    bool Tile::isOnBoard() const {
        return x >= 0 && x <= 7 && y >= 0 && y <= 7;
    }


    bool Tile::operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }


    std::ostream& operator<<(std::ostream& os, const Tile& tile) {
        std::string str;
        str += tile.x + 'a';
        str += tile.y + '1';
        os << str;
        return os;
    }
}
