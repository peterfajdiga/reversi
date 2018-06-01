#include <cmath>
#include <cassert>
#include "AlphaBetaPlayer.h"


namespace reversi {

    AlphaBetaPlayer::AlphaBetaPlayer() : PlayerInterface("Negamax") {};

    AlphaBetaPlayer::AlphaBetaPlayer(const std::string& name) : PlayerInterface(name) {}

    AlphaBetaPlayer::~AlphaBetaPlayer() = default;


    Tile AlphaBetaPlayer::getMove(const Board& board, ViewInterface& view) {
        view.displayStatus(Status::FINDING_MOVE);

        double maxEvalScore = INFINITY * -1;
        Tile bestMove;

        for (const Tile& move : board.getLegalMoves()) {
            Board child(board, move);
            const double evalScore = negamax(child, 4, -INFINITY, INFINITY);
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


    const double VICTORY_MULTIPLIER = 100.0 / 2.0;
    double AlphaBetaPlayer::evaluate(const Board& board) const {
        if (board.isGameOver()) {
            const int whiteAdvantage = board.getScoreWhite() - board.getScoreBlack();
            return whiteAdvantage * VICTORY_MULTIPLIER * board.getGamestate() * getId();
        }

        return board.getLegalMoves().size() * board.getCurrentPlayer() * getId();
    }
}
