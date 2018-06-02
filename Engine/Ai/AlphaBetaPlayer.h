#pragma once

#include "AiPlayerTimed.h"


namespace reversi {

    class AlphaBetaPlayer : public AiPlayerTimed {
    public:
        AlphaBetaPlayer();

        AlphaBetaPlayer(const std::string& name);

        ~AlphaBetaPlayer() override;

        Tile getMoveTimed(const Board& board) override;

        double negamax(const Board& board, int depth, double alpha, double beta) const;

        double evaluate(const Board& board) const;
    };

}
