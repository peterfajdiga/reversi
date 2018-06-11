#include <cassert>
#include <ctime>
#include "NullView.h"
#include "../Engine/Ai/EasyComputerPlayer.h"
#include "../Engine/Ai/AiHeuristicPlayer.h"
#include "../Engine/Ai/Testing/AiHeuristicPlayer2.h"
#include "../Engine/Ai/AlphaBetaPlayer.h"
#include "../Engine/Ai/Testing/AlphaBetaPlayer.h"
#include "../Engine/Ai/MonteCarloPlayer.h"
#include "../Engine/Ai/MonteCarloTreePlayer.h"


int main() {

    using namespace reversi;

    testing::AlphaBetaPlayer player1(white);
    MonteCarloTreePlayer player2(black);
    NullView nullView;

    size_t wins1 = 0;
    size_t wins2 = 0;
    size_t draws = 0;
    size_t winsWhite = 0;
    size_t winsBlack = 0;

    printf(" Games | %13.13s | %13.13s |         draws | cpu time 1 | cpu time 2 |         White |         Black\n", player1.name.c_str(), player2.name.c_str());
    clock_t lastPrint = 0;
    while (true) {
        Board board;
        std::vector<Tile> moveHistory;

        const size_t n_games = winsWhite + winsBlack + draws;
        const bool white1 = n_games % 2 == 0;
        PlayerInterface& playerWhite = white1 ? (PlayerInterface&)player1 : (PlayerInterface&)player2;
        PlayerInterface& playerBlack = white1 ? (PlayerInterface&)player2 : (PlayerInterface&)player1;
        playerWhite.playerColor = white;
        playerBlack.playerColor = black;

        while (!board.isGameOver()) {
            PlayerInterface& currentPlayer = board.getCurrentPlayer() == white ? playerWhite : playerBlack;
            const Tile move = currentPlayer.getMove(board, moveHistory, nullView);
            board.doMove(move);
            moveHistory.emplace_back(move);
        }
        switch (board.getGamestate()) {
            case draw:
                draws++;
                break;
            case white_won:
                winsWhite++;
                (white1 ? wins1 : wins2)++;
                break;
            case black_won:
                winsBlack++;
                (white1 ? wins2 : wins1)++;
                break;
            default: assert(false);
        }
        assert(wins1 + wins2 == winsWhite + winsBlack);

        const clock_t time = clock();
        if (time - lastPrint > 2 * CLOCKS_PER_SEC) {
            const size_t n_games = winsWhite + winsBlack + draws;
            printf("\r%6ld | %6ld (%3.0lf%%) | %6ld (%3.0lf%%) | %6ld (%3.0lf%%) | %9.2lfs | %9.2lfs | %6ld (%3.0lf%%) | %6ld (%3.0lf%%)",
                   n_games,
                   wins1, wins1 * 100.0 / n_games,
                   wins2, wins2 * 100.0 / n_games,
                   draws, draws * 100.0 / n_games,
                   (double)player1.getCpuTime() / CLOCKS_PER_SEC,
                   (double)player2.getCpuTime() / CLOCKS_PER_SEC,
                   winsWhite, winsWhite * 100.0 / n_games,
                   winsBlack, winsBlack * 100.0 / n_games
            );
            fflush(stdout);
            lastPrint = time;
        }
    }
}
