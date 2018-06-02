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

    double AiHeuristicPlayer::heuristic(const Board& board) {
        return heuristics::moves(board);
    }

}
