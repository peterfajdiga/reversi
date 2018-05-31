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

        score getScoreWhite() const;
        score getScoreBlack() const;

        // isOpen
        // Determines if the supplied position (x/y indexes) is open (is empty and not already taken).
        bool isOpen(const Tile& move) const;

        // isLegal
        // Determines if the supplied position (x/y indexes) is a valid move
        // for the current player, i.e., it is on the board, the position is not already filled,
        // and it will flip at least one of the opponent's pieces.
        bool isLegal(const Tile& move) const;

        // perform move
        void doMove(const Tile& move);
        void doNothing();

        // don't overuse
        std::vector<Tile> getLegalMoves() const;

        // canMove
        // Determines if the current player can make a legal move.
        // don't overuse (if you already have a list of legal moves, use that instead)
        bool canMove();

    private:
        color positions[8][8];

        color currentPlayer;

        score scoreWhite, scoreBlack;

        // togglePlayer
        // Toggles currentPlayer between white and black.
        void togglePlayer();
    };

}
