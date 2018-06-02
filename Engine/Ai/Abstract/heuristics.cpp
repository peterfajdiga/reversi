#include "heuristics.h"


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
}
