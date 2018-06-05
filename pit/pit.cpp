#include <cassert>
#include <ctime>
#include "NullView.h"
#include "../Engine/Ai/EasyComputerPlayer.h"
#include "../Engine/Ai/AiHeuristicPlayer.h"
#include "../Engine/Ai/AiHeuristicPlayer2.h"
#include "../Engine/Ai/AlphaBetaPlayer.h"
#include "../Engine/Ai/MonteCarloPlayer.h"
#include "../Engine/Ai/MonteCarloTreePlayer.h"


int main() {

    using namespace reversi;

    MonteCarloTreePlayer playerWhite(white);
    MonteCarloPlayer playerBlack(black);
    NullView nullView;

    size_t winsWhite = 0;
    size_t winsBlack = 0;
    size_t draws = 0;

    printf(" Games | %5.5s (white) | %5.5s (black) |         draws | cpu time white | cpu time black \n", playerWhite.name.c_str(), playerBlack.name.c_str());
    clock_t lastPrint = 0;
    while (true) {
        Board board;
        std::vector<Tile> moveHistory;
        while (!board.isGameOver()) {
            PlayerInterface& currentPlayer = board.getCurrentPlayer() == white ? (AiPlayerTimed&)playerWhite : (AiPlayerTimed&)playerBlack;
            const Tile move = currentPlayer.getMove(board, moveHistory, nullView);
            board.doMove(move);
            moveHistory.emplace_back(move);
        }
        switch (board.getGamestate()) {
            case draw: draws++; break;
            case white_won: winsWhite++; break;
            case black_won: winsBlack++; break;
            default: assert(false);
        }
        clock_t time = clock();
        if (time - lastPrint > 2 * CLOCKS_PER_SEC) {
            const size_t n_games = winsWhite + winsBlack + draws;
            printf("\r%6ld | %6ld (%3.0lf%%) | %6ld (%3.0lf%%) | %6ld (%3.0lf%%) | %13.2lfs | %13.2lfs",
                   n_games,
                   winsWhite, winsWhite * 100.0 / n_games,
                   winsBlack, winsBlack * 100.0 / n_games,
                   draws,     draws     * 100.0 / n_games,
                   (double)playerWhite.getCpuTime() / CLOCKS_PER_SEC,
                   (double)playerBlack.getCpuTime() / CLOCKS_PER_SEC
            );
            fflush(stdout);
            lastPrint = time;
        }
    }
}
