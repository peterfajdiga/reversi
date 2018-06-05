#include <cmath>
#include "MonteCarloPlayer.h"
#include "Abstract/heuristics.h"


namespace reversi {

    MonteCarloPlayer::MonteCarloPlayer(color playerColor) : AiPlayerTimed(playerColor, "Carlos") {}

    MonteCarloPlayer::MonteCarloPlayer(color playerColor, const std::string& name) : AiPlayerTimed(playerColor, name) {}

    MonteCarloPlayer::~MonteCarloPlayer() = default;

    const clock_t SAMPLE_TIME = (clock_t)(3 * CLOCKS_PER_SEC);
    Tile MonteCarloPlayer::getMoveTimed(const Board& board, const std::vector<Tile>& moveHistory) {
        const std::vector<Tile>& legalMoves = board.getLegalMoves();
        const size_t n = legalMoves.size();

        // initialize win counters
        size_t wins[n];
        for (size_t i = 0; i < n; ++i) {
            wins[i] = 0;
        }

        // get child states
        Board children[n];
        for (size_t i = 0; i < n; ++i) {
            children[i] = Board(board, legalMoves[i]);
        }

        // sample
        const clock_t startTime = clock();
        size_t i = 0;
        while (clock() - startTime < SAMPLE_TIME) {
            wins[i] += playRandom(children[i]) / 2 == playerColor;  // increment if this player won
            i = (i + 1) % n;
        }

        // find best move
        Tile bestMove = legalMoves[0];  // default move if winning is not possible
        size_t mostWins = 0;
        for (size_t i = 0; i < n; ++i) {
            if (wins[i] > mostWins) {
                mostWins = wins[i];
                bestMove = legalMoves[i];
            }
        }
        return bestMove;
    }

    gamestate MonteCarloPlayer::playRandom(const Board& boardStart) {
        Board board = boardStart;
        while (!board.isGameOver()) {
            std::vector<Tile> legalMoves = board.getLegalMoves();
            const size_t index = rand() % legalMoves.size();
            board.doMove(legalMoves[index]);
        }
        return board.getGamestate();
    }

    gamestate MonteCarloPlayer::playInformed(const Board& boardStart) {
        Board board = boardStart;
        while (!board.isGameOver()) {
            const std::vector<Tile>& legalMoves = board.getLegalMoves();
            double maxEvalScore = -INFINITY;
            Tile bestMove = legalMoves[0];  // default move if given state is not winnable
            for (const Tile& move : legalMoves) {
                Board child(board, move);
                const double evalScore = heuristics::stability(child) * board.getCurrentPlayer();
                if (evalScore > maxEvalScore) {
                    maxEvalScore = evalScore;
                    bestMove = move;
                }
            }
            board.doMove(bestMove);
        }
        return board.getGamestate();
    }

}
