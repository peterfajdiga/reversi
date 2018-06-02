#pragma once

#include "AiPlayerTimed.h"


namespace reversi {

    class AiEvaluationPlayer : public AiPlayerTimed {
    public:
        AiEvaluationPlayer(color playerColor);

        AiEvaluationPlayer(color playerColor, const std::string& name);

        ~AiEvaluationPlayer() override;

        Tile getMoveTimed(const Board& board) final;

        virtual double evaluateStart(const Board& board) = 0;
    };

}
