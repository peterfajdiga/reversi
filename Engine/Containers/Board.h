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

        score getScore(color player) const;

        // flipPieces
        // Flips each piece in the set of pieces to flip for a given valid move.
        // This sets each identified position's value equal to the current player (`1` or `2`).
        virtual void flipPieces(color playerId);

        // isOpen
        // Determines if the supplied position (x/y indexes) is open (is empty and not already taken).
        bool isOpen(const Tile& move) const;

        // isValidMove
        // Determines if the supplied position (x/y indexes) is a valid move
        // for the current player, i.e., it is on the board, the position is not already filled,
        // and it will flip at least one of the opponent's pieces.
        // Default behaviour will populate mPiecesToFlip with pointers to those board positions
        // that should have their values flipped by the move if it is valid.
        // Set isCheck to `true` to perform a faster check that determines that a move is valid
        // but does not find the complete set of pieces to flip for that move.
        virtual bool isValidMove(const Tile& move, color currentPlayer, bool isCheck);

    private:
        color positions[8][8];


        // Temporary buffer for pieces flipped by a given move.
        std::vector<color*> mPiecesToFlip;
    };

}
