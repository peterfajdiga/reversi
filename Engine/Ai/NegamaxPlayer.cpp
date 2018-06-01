#include <cmath>
#include <cassert>
#include "NegamaxPlayer.h"


namespace reversi {

    NegamaxPlayer::NegamaxPlayer() : PlayerInterface("Negamax") {};

    NegamaxPlayer::NegamaxPlayer(const std::string& name) : PlayerInterface(name) {}

    NegamaxPlayer::~NegamaxPlayer() = default;


    Tile NegamaxPlayer::getMove(const Board& board, ViewInterface& view) {
        view.displayStatus(Status::FINDING_MOVE);

        double maxEvalScore = INFINITY * -1;
        Tile bestMove;

        for (const Tile& move : board.getLegalMoves()) {
            Board child(board, move);
            const double evalScore = negamax(child, 4);
            if (evalScore > maxEvalScore) {
                maxEvalScore = evalScore;
                bestMove = move;
            }
        }
        return bestMove;
    }


    double NegamaxPlayer::negamax(const Board& board, int depth) const {
        if (depth == 0 || board.isGameOver()) {
            return evaluate(board);
        }

        const double sign = board.getCurrentPlayer() * getId();

        double maxEvalScore = -INFINITY;

        for (const Tile& move : board.getLegalMoves()) {
            Board child(board, move);
            const double evalScore = sign * negamax(child, depth - 1);
            maxEvalScore = std::max(maxEvalScore, evalScore);
        }
        return sign * maxEvalScore;
    }


    const double VICTORY_MULTIPLIER = 100.0 / 2.0;
    double NegamaxPlayer::evaluate(const Board& board) const {
        if (board.isGameOver()) {
            const int whiteAdvantage = board.getScoreWhite() - board.getScoreBlack();
            return whiteAdvantage * VICTORY_MULTIPLIER * board.getGamestate() * getId();
        }

        return board.getLegalMoves().size() * board.getCurrentPlayer() * getId();
    }
}
