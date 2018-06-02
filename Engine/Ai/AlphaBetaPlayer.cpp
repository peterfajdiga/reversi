#include <cmath>
#include <cassert>
#include "AlphaBetaPlayer.h"


namespace reversi {

    AlphaBetaPlayer::AlphaBetaPlayer() : AiPlayerTimed("Alphabet") {};

    AlphaBetaPlayer::AlphaBetaPlayer(const std::string& name) : AiPlayerTimed(name) {}

    AlphaBetaPlayer::~AlphaBetaPlayer() = default;


    const double PIECES_GAUSS_A1 =   1.066;
    const double PIECES_GAUSS_B1 =   18.29;
    const double PIECES_GAUSS_C1 =   25.82;
    const double PIECES_GAUSS_A2 = -0.5588;
    const double PIECES_GAUSS_B2 =   6.164;
    const double PIECES_GAUSS_C2 =    9.95;
    double AlphaBetaPlayer::estimateTime(const size_t n_pieces) {
        // pre-learned gauss function for depth 4
        const double exp1 = (n_pieces-PIECES_GAUSS_B1)/PIECES_GAUSS_C1;
        const double exp2 = (n_pieces-PIECES_GAUSS_B2)/PIECES_GAUSS_C2;
        return PIECES_GAUSS_A1 * exp(-exp1 * exp1) +
               PIECES_GAUSS_A2 * exp(-exp2 * exp2);
    }

    const size_t DEPTH_MIN = 4;
    const size_t DEPTH_MAX = 10;
    const size_t DEPTH_D = DEPTH_MAX-DEPTH_MIN;
    size_t AlphaBetaPlayer::estimateDepth(const size_t n_pieces) {
        const double time = estimateTime(n_pieces);
        return (size_t)floor(DEPTH_MAX - time * DEPTH_D);
    }


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

        printf("pieces: %ld | depth: %ld\n", board.getPiecesCount(), estimateDepth(board.getPiecesCount()));

        for (const Tile& move : legalMoves) {
            Board child(board, move);
            const double evalScore = negamax(child, estimateDepth(board.getPiecesCount()), -INFINITY, INFINITY);
            if (evalScore > maxEvalScore) {
                maxEvalScore = evalScore;
                bestMove = move;
            }
        }
        return bestMove;
    }


    double AlphaBetaPlayer::negamax(const Board& board, size_t depth, double alpha, double beta) const {
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
