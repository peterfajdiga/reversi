#include "ReversiGameConsoleView.h"


int main(int argc, char** argv)
{
	ReversiGameEngine game;
	ReversiGameConsoleView view;

	game.setView(&view);
	game.runGame();

	return 0;
}