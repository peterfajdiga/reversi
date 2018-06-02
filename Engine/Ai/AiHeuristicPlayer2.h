#pragma once

#include "AiEvaluationPlayer.h"


namespace reversi {

    class AiHeuristicPlayer2 : public AiEvaluationPlayer {
    public:
        AiHeuristicPlayer2(color playerColor);

        AiHeuristicPlayer2(color playerColor, const std::string& name);

        ~AiHeuristicPlayer2() override;

        double evaluateStart(const Board& board) override;
    };

}
