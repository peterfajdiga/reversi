#pragma once

#include "Abstract/AiEvaluationPlayer.h"


namespace reversi {

    class AlphaBetaPlayer : public AiEvaluationPlayer {
    public:
        AlphaBetaPlayer(color playerColor);

        AlphaBetaPlayer(color playerColor, const std::string& name);

        ~AlphaBetaPlayer() override;

        static double estimateTimeByPieces(const size_t n_pieces);

        static double estimateTimeByMoves(const size_t n_moves);

        static size_t estimateDepth(const size_t n_pieces, const size_t n_moves);

        double evaluateStart(const Board& board) override;

        double negamax(const Board& board, size_t depth, double alpha, double beta);

        double heuristic(const Board& board) override;
    };

}
