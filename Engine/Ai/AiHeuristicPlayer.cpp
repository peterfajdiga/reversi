#include <cmath>
#include "AiHeuristicPlayer.h"


namespace reversi {
    
    AiHeuristicPlayer::AiHeuristicPlayer(color playerColor) : AiEvaluationPlayer(playerColor, "Heuristic") {}

    AiHeuristicPlayer::AiHeuristicPlayer(color playerColor, const std::string& name) : AiEvaluationPlayer(playerColor, name) {}

    AiHeuristicPlayer::~AiHeuristicPlayer() = default;

    double AiHeuristicPlayer::evaluateStart(const Board& board) {
        if (board.isGameOver()) {
            const gamestate state = board.getGamestate();
            if (state == draw) {
                return 0.0;
            } else {
                return INFINITY * state * playerColor;
            }
        }

        return board.getLegalMoves().size() * board.getCurrentPlayer() * playerColor;
    }
    
}
