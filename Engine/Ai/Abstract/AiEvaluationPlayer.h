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

        // optional
        double evaluate(const Board& board);

        // optional
        // positive value good for white player
        virtual double heuristic(const Board& board) {return 0.0;}
    };

}
