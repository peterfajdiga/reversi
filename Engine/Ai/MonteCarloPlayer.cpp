#include <cmath>
#include "MonteCarloPlayer.h"


namespace reversi {

    MonteCarloPlayer::MonteCarloPlayer() : PlayerInterface("Carlos") {}

    MonteCarloPlayer::MonteCarloPlayer(const std::string& name) : PlayerInterface(name) {}

    MonteCarloPlayer::~MonteCarloPlayer() = default;

    Tile MonteCarloPlayer::getMove(const Board& board, ViewInterface& view) {
        view.displayStatus(Status::FINDING_MOVE);

        double maxEvalScore = INFINITY * -1;
        Tile bestMove;

        for (const Tile& move : board.getLegalMoves()) {
            Board child(board, move);
            const double evalScore = evaluateMC(child);
            if (evalScore > maxEvalScore) {
                maxEvalScore = evalScore;
                bestMove = move;
            }
        }
        return bestMove;
    }

    const size_t N_RUNS = 1000;
    double MonteCarloPlayer::evaluateMC(const Board& board) const {
        size_t wins = 0;
        for (int run = 0; run < N_RUNS; ++run) {
            Board boardCopy = board;
            playRandom(boardCopy);
            if (boardCopy.getGamestate() / 2 == getId()) {
                wins++;
            }
        }
        return (double)wins / N_RUNS;
    }

    void MonteCarloPlayer::playRandom(Board& board) {
        while (!board.isGameOver()) {
            std::vector<Tile> legalMoves = board.getLegalMoves();
            const size_t index = rand() % legalMoves.size();
            board.doMove(legalMoves[index]);
        }
    }

}
