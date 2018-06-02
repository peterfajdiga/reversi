#include <cmath>
#include "AiHeuristicPlayer2.h"
#include "Abstract/heuristics.h"


namespace reversi {

    AiHeuristicPlayer2::AiHeuristicPlayer2(color playerColor) : AiEvaluationPlayer(playerColor, "Heuristic") {}

    AiHeuristicPlayer2::AiHeuristicPlayer2(color playerColor, const std::string& name) : AiEvaluationPlayer(playerColor, name) {}

    AiHeuristicPlayer2::~AiHeuristicPlayer2() = default;

    double AiHeuristicPlayer2::evaluateStart(const Board& board) {
        return evaluate(board);
    }

    double AiHeuristicPlayer2::heuristic(const Board& board) {
        return heuristics::stanford_modified_4_8(board);
    }

}
