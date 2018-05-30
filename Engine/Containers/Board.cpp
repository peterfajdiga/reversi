#include <vector>
#include <assert.h>
#include "Board.h"
#include "Direction.h"


namespace reversi {

    // Directions table used for finding valid moves.
    // Each table value is a vector (math vector, not a C++ STL data structure!)
    // representing one of the eight directions to check (up, up-right, right, etc.)
    const Direction sDirectionsTable[8] = {
            // { x, y }
            {  0,  1 },  // up
            {  1,  1 },  // up-left
            {  1,  0 },  // left
            {  1, -1 },  // down-left
            {  0, -1 },  // down
            { -1, -1 },  // down-right
            { -1,  0 },  // right
            { -1,  1 }   // up-right
    };


    Board::Board() {
        for (int y = 0; y < 8; ++y) {
            for (int x = 0; x < 8; ++x) {
                positions[x][y] = unoccupied;
            }
        }

        // initialize starting positions for each player
        positions[3][3] = black;
        positions[3][4] = white;
        positions[4][3] = white;
        positions[4][4] = black;

        currentPlayer = white;
    }


    color& Board::operator[] (const Tile &tile) {
        return positions[tile.x][tile.y];
    }
    const color& Board::operator[] (const Tile &tile) const {
        return positions[tile.x][tile.y];
    }

    color& Board::operator()(coordinate x, coordinate y) {
        return positions[x][y];
    }
    const color& Board::operator()(coordinate x, coordinate y) const {
        return positions[x][y];
    }


    color Board::getCurrentPlayer() const {
        return currentPlayer;
    }


    score Board::getScore(color player) const {
        score sum = 0;
        for (size_t y = 0; y < 8; y++) {
            for (size_t x = 0; x < 8; x++) {
                sum += positions[x][y] == player;  // increment if player holds xy tile
            }
        }
        return sum;
    }


    bool Board::isOpen(const Tile& move) const {
        return positions[move.x][move.y] == 0;
    }


    bool Board::isValidMove(const Tile& move) const {
        size_t flipCount = 0;

        // for each direction from the piece position
        // look for one or more adjacent pieces of the opposing player
        // followed by a piece of this player
        // max of 7 steps can be taken in any given direction
        // take 8 steps so that the last check is off the board
        // and will clear mPossiblePiecesToFlip if we get there
        for (const Direction direction : sDirectionsTable) {
            // init position and step

            // short-circuit search based on proximity to edge and direction vector
            // e.g. a position in the first two rows of the board does not need to
            // search in the up-right, up, or up-left directions (yStep = 1) because
            // no pieces can be flipped in that direction
            // yStep is inverted with respect to board array index
            if (move.y <= 1 && direction.y == 1 || move.y >= 6 && direction.y == -1 || move.x <= 1 && direction.x == -1 || move.x >= 6 && direction.x == 1) {
                continue;
            }

            bool validMove = false;

            // max of 7 steps can be taken in any given direction
            // take 8 steps so that the last check is off the board
            // and will clear flippablePieces if we get there
            Tile move_step(move);
            for (size_t step = 0; step < 8; step++) {
                // apply step in direction
                // step is represented as a math vector
                // yStep is inverted with respect to board array index
                move_step.x += direction.x;
                move_step.y -= direction.y;

                // check bounds and empty position
                if (!move_step.isOnBoard() || isOpen(move_step)) {
                    // no flipped pieces in this direction
                    validMove = false;

                    // stop searching in this direction
                    break;
                }

                // check for own piece
                if (positions[move_step.x][move_step.y] == currentPlayer) {
                    // stop searching in this direction
                    break;
                }

                // found opposing piece
                validMove = true;
            }

            if (validMove) {
                return true;
            }
        }

        return false;
    }

    void Board::doMove(const Tile& move) {
        size_t flipCount = 0;

        std::vector<color*> mPiecesToFlip;

        // for each direction from the piece position
        // look for one or more adjacent pieces of the opposing player
        // followed by a piece of this player
        // max of 7 steps can be taken in any given direction
        // take 8 steps so that the last check is off the board
        // and will clear mPossiblePiecesToFlip if we get there
        for (const Direction direction : sDirectionsTable) {
            // init position and step

            // short-circuit search based on proximity to edge and direction vector
            // e.g. a position in the first two rows of the board does not need to
            // search in the up-right, up, or up-left directions (yStep = 1) because
            // no pieces can be flipped in that direction
            // yStep is inverted with respect to board array index
            if (move.y <= 1 && direction.y == 1 || move.y >= 6 && direction.y == -1 || move.x <= 1 && direction.x == -1 || move.x >= 6 && direction.x == 1) {
                continue;
            }

            std::vector<color*> flippablePieces;

            // max of 7 steps can be taken in any given direction
            // take 8 steps so that the last check is off the board
            // and will clear flippablePieces if we get there
            Tile move_step(move);
            for (size_t step = 0; step < 8; step++) {
                // apply step in direction
                // step is represented as a math vector
                // yStep is inverted with respect to board array index
                move_step.x += direction.x;
                move_step.y -= direction.y;

                // check bounds and empty position
                if (!move_step.isOnBoard() || isOpen(move_step)) {
                    // no flipped pieces in this direction
                    flippablePieces.clear();

                    // stop searching in this direction
                    break;
                }

                // check for own piece
                if (positions[move_step.x][move_step.y] == currentPlayer) {
                    // stop searching in this direction
                    break;
                }

                // found opposing piece
                // save a reference to this piece
                // and continue searching in this direction
                flippablePieces.emplace_back(&positions[move_step.x][move_step.y]);
            }

            for (color* flippablePiece : flippablePieces) {
                // save reference to flippable piece
                mPiecesToFlip.emplace_back(flippablePiece);
                // increment flipCount
                flipCount++;
            }
        }

        if (flipCount == 0) {
            throw InvalidMoveException();
        }
        (*this)[move] = currentPlayer;

        // flip pieces
        for (color* pieceToFlip : mPiecesToFlip) {
            *pieceToFlip = currentPlayer;
        }

        togglePlayer();
    }

    void Board::doNothing() {
        assert (!canMove());
        togglePlayer();
    }


    std::vector<Tile> Board::getLegalMoves() const {
        std::vector<Tile> legalMoves;
        for (Tile move(0, 0); move.y < 8; move.y++) {
            for (move.x = 0; move.x < 8; move.x++) {
                // check open position and valid move
                // set isCheck flag to shorten isValidMove search
                if (isOpen(move) && isValidMove(move)) {
                    legalMoves.emplace_back(move);
                }
            }
        }
        return legalMoves;
    }


    bool Board::canMove() {
        return !getLegalMoves().empty();
    }

    void Board::togglePlayer() {
        // bitwise xor with 3 will toggle between 1 and 2
        assert (currentPlayer == white || currentPlayer == black);
        currentPlayer = (color)(currentPlayer ^ 3);
    }

}
