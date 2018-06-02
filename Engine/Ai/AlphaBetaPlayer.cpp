#include <cmath>
#include <cassert>
#include "AlphaBetaPlayer.h"


namespace reversi {

    AlphaBetaPlayer::AlphaBetaPlayer() : AiPlayerTimed("Alphabet") {};

    AlphaBetaPlayer::AlphaBetaPlayer(const std::string& name) : AiPlayerTimed(name) {}

    AlphaBetaPlayer::~AlphaBetaPlayer() = default;

    const double weights[8][8] = {
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160}
    };


    Tile AlphaBetaPlayer::getMoveTimed(const Board& board) {
        const std::vector<Tile>& legalMoves = board.getLegalMoves();
        double maxEvalScore = -INFINITY;
        Tile bestMove = legalMoves[0];  // default move if given state is not winnable

        for (const Tile& move : legalMoves) {
            Board child(board, move);
            const double evalScore = negamax(child, 8, -INFINITY, INFINITY);
            if (evalScore > maxEvalScore) {
                maxEvalScore = evalScore;
                bestMove = move;
            }
        }
        return bestMove;
    }


    double AlphaBetaPlayer::negamax(const Board& board, int depth, double alpha, double beta) const {
        if (depth == 0 || board.isGameOver()) {
            return evaluate(board);
        }

        if (board.getCurrentPlayer() == getId()) {
            // my turn
            double maxEvalScore = -INFINITY;

            for (const Tile& move : board.getLegalMoves()) {
                Board child(board, move);
                const double evalScore = negamax(child, depth - 1, alpha, beta);
                maxEvalScore = std::max(maxEvalScore, evalScore);
                alpha = std::max(alpha, maxEvalScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return maxEvalScore;

        } else {
            // opponent's turn
            double minEvalScore = INFINITY;

            for (const Tile& move : board.getLegalMoves()) {
                Board child(board, move);
                const double evalScore = negamax(child, depth - 1, alpha, beta);
                minEvalScore = std::min(minEvalScore, evalScore);
                beta = std::min(beta, minEvalScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return minEvalScore;
        }
    }


    double AlphaBetaPlayer::evaluate(const Board& board) const {
        if (board.isGameOver()) {
            const gamestate state = board.getGamestate();
            if (state == draw) {
                return 0.0;
            } else {
                return INFINITY * state * getId();
            }
        }

        return board.getLegalMoves().size() * board.getCurrentPlayer() * getId();
    }
}
