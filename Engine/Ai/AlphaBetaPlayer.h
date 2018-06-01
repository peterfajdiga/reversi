#pragma once

#include "../PlayerInterface.h"


namespace reversi {

    class AlphaBetaPlayer : public PlayerInterface {
    public:
        AlphaBetaPlayer();

        AlphaBetaPlayer(const std::string& name);

        ~AlphaBetaPlayer() override;

        Tile getMove(const Board& board, ViewInterface& view) override;

        double negamax(const Board& board, int depth, double alpha, double beta) const;

        double evaluate(const Board& board) const;
    };

}
