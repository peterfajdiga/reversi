#include <cmath>
#include "AiEvaluationPlayer.h"


namespace reversi {

    AiEvaluationPlayer::AiEvaluationPlayer(color playerColor) : AiPlayerTimed(playerColor) {}

    AiEvaluationPlayer::AiEvaluationPlayer(color playerColor, const std::string& name) : AiPlayerTimed(playerColor, name) {}

    AiEvaluationPlayer::~AiEvaluationPlayer() = default;

    Tile AiEvaluationPlayer::getMoveTimed(const Board& board) {
        const std::vector<Tile>& legalMoves = board.getLegalMoves();
        double maxEvalScore = -INFINITY;
        Tile bestMove = legalMoves[0];  // default move if given state is not winnable

        for (const Tile& move : legalMoves) {
            Board child(board, move);
            const double evalScore = evaluateStart(child);
            if (evalScore > maxEvalScore) {
                maxEvalScore = evalScore;
                bestMove = move;
            }
        }
        return bestMove;
    }
}
