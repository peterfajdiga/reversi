#pragma once

namespace reversi {

    typedef char dcoor;

    struct Direction {
        dcoor x, y;
    };

    // Directions table used for finding valid moves.
    // Each table value is a vector (math vector, not a C++ STL data structure!)
    // representing one of the eight directions to check (up, up-right, right, etc.)
    const Direction DIRECTIONS[8] = {
            // { x, y }
            {  0,  1 },  // ↓
            {  0, -1 },  // ↑
            {  1,  0 },  // →
            { -1,  0 },  // ←
            {  1,  1 },  // ↘
            {  1, -1 },  // ↗
            { -1,  1 },  // ↙
            { -1, -1 }   // ↖
    };

}
