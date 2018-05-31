#pragma once

#include <vector>
#include "Tile.h"
#include "../constants.h"

namespace reversi {

    //  xy               x  y
    // "a1" == positions[0][0]
    // "a2" == positions[0][1]
    // "b1" == positions[1][0]
    // "h8" == positions[7][7]
    class Board {
    public:
        Board();

        color& operator[] (const Tile &tile);
        const color& operator[] (const Tile &tile) const;

        color& operator() (coordinate x, coordinate y);
        const color& operator() (coordinate x, coordinate y) const;

        color getCurrentPlayer() const;

        score getScore(color player) const;

        // isOpen
        // Determines if the supplied position (x/y indexes) is open (is empty and not already taken).
        bool isOpen(const Tile& move) const;

        // isLegal
        // Determines if the supplied position (x/y indexes) is a valid move
        // for the current player, i.e., it is on the board, the position is not already filled,
        // and it will flip at least one of the opponent's pieces.
        virtual bool isLegal(const Tile& move) const;

        // perform move
        virtual void doMove(const Tile& move);
        virtual void doNothing();

        std::vector<Tile> getLegalMoves() const;

        // canMove
        // Determines if the current player can make a legal move.
        virtual bool canMove();

    private:
        color positions[8][8];

        color currentPlayer;

        // togglePlayer
        // Toggles mCurrentPlayer between `1` and `2`.
        virtual void togglePlayer();
    };

}
