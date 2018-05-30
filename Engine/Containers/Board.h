#pragma once

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

        id& operator[] (const Tile &tile);
        const id& operator[] (const Tile &tile) const;

        id& operator() (coordinate x, coordinate y);
        const id& operator() (coordinate x, coordinate y) const;

        score getScore(id player) const;

        // flipPieces
        // Flips each piece in the set of pieces to flip for a given valid move.
        // This sets each identified position's value equal to the current player (`1` or `2`).
        virtual void flipPieces(id playerId);

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
        virtual bool isValidMove(const Tile& move, id currentPlayer, bool isCheck);

        // initPiecesToFlip
        // Initializes the set of pieces to flip for a given valid move.
        virtual void initPiecesToFlip();

        // initPossiblePiecesToFlip
        // Initializes the set of pieces that are possibly flipped when evaluating
        // a position as a valid move.
        virtual void initPossiblePiecesToFlip();

    private:
        id positions[8][8];


        // The maximum number of pieces to flip in a given direction is 6, but the
        // maximum number of positions that could be queued while searching is 8.
        static const int sMaxPossiblePiecesToFlipPerDirection = 8;

        static const int sMaxPiecesToFlipPerMove = 19;

        // Temporary buffer for pieces flipped by a given move.
        id* mPiecesToFlip[sMaxPiecesToFlipPerMove];

        // Temporary buffer for pieces flipped in a given direction for a given move.
        id* mPossiblePiecesToFlip[sMaxPossiblePiecesToFlipPerDirection];
    };

}
