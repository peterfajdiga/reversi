#include <cmath>
#include "MonteCarloPlayer.h"


namespace reversi {

    MonteCarloPlayer::MonteCarloPlayer(color playerColor) : AiPlayerTimed(playerColor, "Carlos") {}

    MonteCarloPlayer::MonteCarloPlayer(color playerColor, const std::string& name) : AiPlayerTimed(playerColor, name) {}

    MonteCarloPlayer::~MonteCarloPlayer() = default;

    Tile MonteCarloPlayer::getMoveTimed(const Board& board) {
        double maxEvalScore = -INFINITY;
        Tile bestMove;

        for (const Tile& move : board.getLegalMoves()) {
            Board child(board, move);
            const double evalScore = sampleMC(child);
            if (evalScore > maxEvalScore) {
                maxEvalScore = evalScore;
                bestMove = move;
            }
        }
        return bestMove;
    }

    const size_t N_RUNS = 1000;
    double MonteCarloPlayer::sampleMC(const Board& board) const {
        size_t wins = 0;
        for (int run = 0; run < N_RUNS; ++run) {
            if (playRandom(board)) {
                wins++;
            }
        }
        return (double)wins / N_RUNS;
    }

    bool MonteCarloPlayer::playRandom(const Board& boardStart) const {
        Board board = boardStart;
        while (!board.isGameOver()) {
            std::vector<Tile> legalMoves = board.getLegalMoves();
            const size_t index = rand() % legalMoves.size();
            board.doMove(legalMoves[index]);
        }
        return board.getGamestate() / 2 == playerColor;
    }

}
