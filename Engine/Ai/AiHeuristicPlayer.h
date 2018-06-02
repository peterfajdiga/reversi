#pragma once

#include "Abstract/AiEvaluationPlayer.h"


namespace reversi {

    class AiHeuristicPlayer : public AiEvaluationPlayer {
    public:
        AiHeuristicPlayer(color playerColor);

        AiHeuristicPlayer(color playerColor, const std::string& name);

        ~AiHeuristicPlayer() override;

        double evaluateStart(const Board& board) override;

        double heuristic(const Board& board) override;
    };

}
