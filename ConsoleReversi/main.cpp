#include "ConsoleView.h"


int main(int argc, char** argv) {
    reversi::PlayerInterface* player1 = new reversi::HumanPlayer();
    reversi::PlayerInterface* player2 = new reversi::HumanPlayer();

    reversi::Engine game(player1, player2);
    reversi::ConsoleView view;

    game.setView(&view);
    game.runGame();

    // players are deleted in reversi::Engine  // TODO: change that

    return 0;
}
