#include <cassert>
#include <ctime>
#include "../Engine/Ai/EasyComputerPlayer.h"
#include "../Engine/Ai/AiHeuristicPlayer.h"
#include "NullView.h"
#include "../Engine/Ai/AiHeuristicPlayer2.h"
#include "../Engine/Ai/AlphaBetaPlayer.h"
#include "../Engine/Ai/MonteCarloPlayer.h"


int main() {

    using namespace reversi;

    MonteCarloPlayer playerWhite(white);
    AlphaBetaPlayer playerBlack(black);
    NullView nullView;

    size_t winsWhite = 0;
    size_t winsBlack = 0;
    size_t draws = 0;

    printf("%s (white) : %s (black)\n", playerWhite.name.c_str(), playerBlack.name.c_str());
    clock_t lastPrint = 0;
    while (true) {
        Board board;
        while (!board.isGameOver()) {
            PlayerInterface& currentPlayer = board.getCurrentPlayer() == white ? (AiPlayerTimed&)playerWhite : (AiPlayerTimed&)playerBlack;
            const Tile move = currentPlayer.getMove(board, nullView);
            board.doMove(move);
        }
        switch (board.getGamestate()) {
            case draw: draws++; break;
            case white_won: winsWhite++; break;
            case black_won: winsBlack++; break;
            default: assert(false);
        }
        clock_t time = clock();
        if (time - lastPrint > 2 * CLOCKS_PER_SEC) {
            printf("\r%ld : %ld (%ld draws)", winsWhite, winsBlack, draws);
            fflush(stdout);
            lastPrint = time;
        }
    }
}
