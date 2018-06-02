#pragma once

#include "AiPlayerTimed.h"


namespace reversi {

    class AlphaBetaPlayer : public AiPlayerTimed {
    public:
        AlphaBetaPlayer();

        AlphaBetaPlayer(const std::string& name);

        ~AlphaBetaPlayer() override;

        static double estimateTimeByPieces(const size_t n_pieces);

        static double estimateTimeByMoves(const size_t n_moves);

        static size_t estimateDepth(const size_t n_pieces, const size_t n_moves);

        Tile getMoveTimed(const Board& board) override;

        double negamax(const Board& board, size_t depth, double alpha, double beta) const;

        double evaluate(const Board& board) const;
    };

}
