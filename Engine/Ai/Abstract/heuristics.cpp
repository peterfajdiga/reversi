#include "heuristics.h"
#include "../../Containers/Direction.h"
#include "../../Containers/edges.h"


namespace reversi::heuristics {

    const double TILE_WEIGHTS[8][8] = {
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160}
    };

    double stanford(const Board& board) {
        double boardValue = 0.0;
        for (coordinate y = 0; y < 8; ++y) {
            for (coordinate x = 0; x < 8; ++x) {
                boardValue += board(x, y) * TILE_WEIGHTS[x][y];
            }
        }
        return boardValue;
    }

    double stanford_modified(const Board& board) {
        double weightsModified[8][8];
        std::copy(&TILE_WEIGHTS[0][0], &TILE_WEIGHTS[0][0]+64, &weightsModified[0][0]);

        if(board(0,0)== board.getCurrentPlayer()){
            weightsModified[0][1] *= -1;
            weightsModified[1][0] *= -1;
            weightsModified[1][1] *= -1;
        }
        if(board(7,7)== board.getCurrentPlayer()){
            weightsModified[7][6] *= -1;
            weightsModified[6][7] *= -1;
            weightsModified[6][6] *= -1;
        }
        if(board(0,7)== board.getCurrentPlayer()){
            weightsModified[0][6] *= -1;
            weightsModified[1][7] *= -1;
            weightsModified[1][6] *= -1;
        }
        if(board(7,0)== board.getCurrentPlayer()){
            weightsModified[7][1] *= -1;
            weightsModified[6][0] *= -1;
            weightsModified[6][1] *= -1;
        }
        double boardValue = 0.0;
        for (coordinate y = 0; y < 8; ++y) {
            for (coordinate x = 0; x < 8; ++x) {
                boardValue += board(x, y) * weightsModified[x][y];
            }
        }

        return boardValue;
    }

    double stanford_modified_4_8(const Board& board) {
        double weightsModified[8][8];
        std::copy(&TILE_WEIGHTS[0][0], &TILE_WEIGHTS[0][0]+64, &weightsModified[0][0]);

        if(board(0,0)== board.getCurrentPlayer()){
            weightsModified[0][1] *= -1;
            weightsModified[1][0] *= -1;
            weightsModified[1][1] *= -1;
        }
        if(board(7,7)== board.getCurrentPlayer()){
            weightsModified[7][6] *= -1;
            weightsModified[6][7] *= -1;
            weightsModified[6][6] *= -1;
        }
        if(board(0,7)== board.getCurrentPlayer()){
            weightsModified[0][6] *= -1;
            weightsModified[1][7] *= -1;
            weightsModified[1][6] *= -1;
        }
        if(board(7,0)== board.getCurrentPlayer()){
            weightsModified[7][1] *= -1;
            weightsModified[6][0] *= -1;
            weightsModified[6][1] *= -1;
        }
        double boardValue = 0.0;
        for (coordinate y = 0; y < 8; ++y) {
            for (coordinate x = 0; x < 8; ++x) {
                boardValue += 4.8 * board(x, y) * weightsModified[x][y];
            }
        }

        return boardValue;
    }

    double moves(const Board& board) {
        return board.getLegalMoves().size() * board.getCurrentPlayer();
    }

    const double STABILITY_POS = 1.0;
    const double STABILITY_NEG = -1.0;
    double stability(const Board& board) {
        double score = 0.0;

        for (size_t i_direction = 0; i_direction < 8; i_direction++) {
            const Direction& direction = DIRECTIONS[i_direction];

            for (const Tile& start : edges::EDGES[i_direction]) {
                Tile tile = start;
                const color startingColor = board[tile];
                bool penaltyRequired = false;

                for (size_t i = 0; i < 8; ++i) {
                    if (!tile.isOnBoard()) {
                        break;
                    }
                    const color currentColor = board[tile];

                    if (currentColor == unoccupied) {
                        penaltyRequired = true;

                    } else if (penaltyRequired) {
                        score += STABILITY_NEG * currentColor;
                        break;

                    } else if (currentColor == startingColor) {
                        score += STABILITY_POS * currentColor;

                    } else {
                        score += STABILITY_NEG * currentColor;
                        break;  // TODO: maybe not?
                    }

                    tile.x += direction.x;
                    tile.y += direction.y;
                }
            }
        }
        return score;
    }
}
