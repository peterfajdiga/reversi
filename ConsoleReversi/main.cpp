#include "ConsoleView.h"


int main(int argc, char** argv) {
    reversi::Engine game;
    reversi::ConsoleView view;

    game.setView(&view);
    game.runGame();

    return 0;
}
