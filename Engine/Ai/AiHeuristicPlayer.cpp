#include <cmath>
#include "AiHeuristicPlayer.h"
#include "Abstract/heuristics.h"


namespace reversi {
    
    AiHeuristicPlayer::AiHeuristicPlayer(color playerColor) : AiEvaluationPlayer(playerColor, "Heuristic") {}

    AiHeuristicPlayer::AiHeuristicPlayer(color playerColor, const std::string& name) : AiEvaluationPlayer(playerColor, name) {}

    AiHeuristicPlayer::~AiHeuristicPlayer() = default;

    double AiHeuristicPlayer::evaluateStart(const Board& board) {
        return evaluate(board);
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
                boardValue += board(x, y) * weightsModified[x][y];
            }
        }

        const double legalMovesValue =  board.getLegalMoves().size() * board.getCurrentPlayer(); // * getId();
        //if(board.getPiecesCount() >= 40) return (boardValue + legalMovesValue) * playerColor;
        return (boardValue) * playerColor;
    double AiHeuristicPlayer::heuristic(const Board& board) {
        return heuristics::moves(board);
    }

}
