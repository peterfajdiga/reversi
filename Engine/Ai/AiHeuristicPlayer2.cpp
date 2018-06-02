#include <cmath>
#include "AiHeuristicPlayer2.h"


namespace reversi {

    AiHeuristicPlayer2::AiHeuristicPlayer2(color playerColor) : AiEvaluationPlayer(playerColor, "Heuristic") {}

    AiHeuristicPlayer2::AiHeuristicPlayer2(color playerColor, const std::string& name) : AiEvaluationPlayer(playerColor, name) {}

    AiHeuristicPlayer2::~AiHeuristicPlayer2() = default;

    const double weights[8][8] = {
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160}
    };

    double AiHeuristicPlayer2::evaluateStart(const Board& board) {
        if (board.isGameOver()) {
            const gamestate state = board.getGamestate();
            if (state == draw) {
                return 0.0;
            } else {
                return INFINITY * state * playerColor;
            }
        }

        double weightsModified[8][8];
        std::copy(&weights[0][0], &weights[0][0]+8*8,&weightsModified[0][0]);


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
                boardValue += 4.8*(board(x, y) * weightsModified[x][y]);
            }
        }

        const double legalMovesValue =  board.getLegalMoves().size() * board.getCurrentPlayer(); // * getId();
        //if(board.getPiecesCount() >= 40) return (boardValue + legalMovesValue) * playerColor;
        const double prog = board.getProgression() * 0.1;
        const double progn = 1.0 - prog;
        return (boardValue) * playerColor;
    }

}
