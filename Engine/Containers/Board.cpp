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

    score Board::getScore(color player) const {
        score sum = 0;
        for (size_t y = 0; y < 8; y++) {
            for (size_t x = 0; x < 8; x++) {
                sum += positions[x][y] == player;  // increment if player holds xy tile
            }
        }
        return sum;
    }


    void Board::flipPieces(color playerId) {
        int i;

        for (i = 0; i < sMaxPiecesToFlipPerMove; i++) {
            if (mPiecesToFlip[i] == NULL) {
                break;
            }

            *mPiecesToFlip[i] = playerId;
        }
    }


    bool Board::isOpen(const Tile& move) const {
        return positions[move.x][move.y] == 0;
    }


    bool Board::isValidMove(const Tile& move, color currentPlayer, bool isCheck) {
        size_t flipCount = 0;

        initPiecesToFlip();

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

            initPossiblePiecesToFlip();

            // max of 7 steps can be taken in any given direction
            // take 8 steps so that the last check is off the board
            // and will clear mPossiblePiecesToFlip if we get there
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
                    initPossiblePiecesToFlip();

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
                mPossiblePiecesToFlip[step] = &positions[move_step.x][move_step.y];
            }

            for (size_t j = 0; j < sMaxPossiblePiecesToFlipPerDirection; j++) {
                if (mPossiblePiecesToFlip[j] == nullptr) {
                    break;
                }

                // at this point, the position is a valid move
                // stop searching if isCheck is `true`
                if (isCheck) {
                    return true;
                }

                // save reference to flippable piece
                // increment flipCount
                mPiecesToFlip[flipCount++] = mPossiblePiecesToFlip[j];
            }
        }

        return flipCount > 0;  // if any of the opponent's pieces will be flipped, it's a valid move
    }


    void Board::initPiecesToFlip() {
        for (size_t i = 0; i < sMaxPiecesToFlipPerMove; i++) {
            mPiecesToFlip[i] = NULL;
        }
    }

    void Board::initPossiblePiecesToFlip() {
        for (size_t i = 0; i < sMaxPossiblePiecesToFlipPerDirection; i++) {
            mPossiblePiecesToFlip[i] = NULL;
        }
    }

}
