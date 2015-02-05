#pragma once

#include <iostream>
#include "ConsoleView.h"


namespace reversi {

	ConsoleView::ConsoleView()
	{

	}


	ConsoleView::~ConsoleView()
	{

	}


	void ConsoleView::setupGame(const Engine& engine)
	{
		using namespace std;

		cout << "\n\nConsole Reversi by jsmreese.\n\n";
		cout << "At any time, enter 'n' for a new game or 'q' to quit playing.\n\n";
		cout << "To make a move, enter the column letter followed by\n";
		cout << "the row number of the desired position, e.g. 'f4'.\n\n";
		cout << "Columns are from 'a' to 'h', and rows are from '1' to '8'." << endl;
	}


	void ConsoleView::teardownGame(const Engine& engine)
	{

	}


	std::string ConsoleView::promptInput(const Engine& engine, bool isGameOver)
	{
		using namespace std;

		string input;
		int s1 = engine.getPlayer(1).getScore();
		int s2 = engine.getPlayer(2).getScore();

		if (isGameOver) {
			cout << "\n\n-----------------------------";
			cout << "\n\n" + drawBoard(engine) << endl;

			cout << "\n ** Game Over **\n\n";
			cout << "\n\nScore\n";
			cout << engine.getPlayer(1).getName();
			cout << ": " + to_string(s1) + "\n";
			cout << engine.getPlayer(2).getName();
			cout << ": " + to_string(s2) + "\n";

			if (s1 == s2) {
				cout << "Game is a draw!" << endl;
			}
			else {
				cout << "\n Congratulations, ";
				cout << engine.getPlayer(s1 > s2 ? 1 : 2).getName() + "!" << endl;
			}

			cout << "\n\nEnter 'n' to play again, or 'q' to quit playing: ";

			cin >> input;

			return input;
		}

		cout << "\n\n-----------------------------";

		cout << "\n\nScore\n";
		cout << engine.getPlayer(1).getName();
		cout << ": " + to_string(engine.getPlayer(1).getScore()) + "\n";
		cout << engine.getPlayer(2).getName();
		cout << ": " + to_string(engine.getPlayer(2).getScore()) + "\n";

		cout << "\n\n" + drawBoard(engine) + "\n";

		cout << "\n" + engine.getPlayer().getName() + ", enter a move: ";
		cin >> input;

		return input;
	}


	void ConsoleView::displayStatus(const Engine& engine, Status status, const std::string& input)
	{
		using namespace std;

		switch (status) {
		case Status::CANNOT_MOVE:
			cout << "\n\n ** " + engine.getPlayer().getName() + " is unable to move. **" << endl;
			break;

		case Status::INVALID_MOVE:
			cout << "\n\n ** Invalid move. Move must flip at least one of the opponent's pieces. **" << endl;
			break;

		case Status::OUT_OF_BOUNDS:
			cout << "\n\n ** Invalid move. Position is not on the board. **" << endl;
			break;

		case Status::POSITION_FILLED:
			cout << "\n\n ** Invalid move. Position is already filled. **" << endl;
			break;

		case Status::SUCCESS:
			cout << "\n\n" + engine.getPlayer().getName() + " moved at position " + input + "." << endl;
			break;

		case Status::FINDING_MOVE:
			cout << "\n\n" + engine.getPlayer().getName() + " searching for move..." << endl;
			break;
		}
	}


	std::string ConsoleView::drawBoard(const Engine& engine)
	{
		using namespace std;

		int i, j, position;
		string board = "   a b c d e f g h\n\n";

		for (j = 0; j < 8; j++) {
			board += to_string(j + 1) + " ";
			for (i = 0; i < 8; i++) {
				position = engine.getPosition(i, j);
				if (position == 0) {
					board += " .";
				}
				else {
					board += " " + to_string(position);
				}
			}

			board += "  " + to_string(j + 1) + "\n";
		}

		board += "\n   a b c d e f g h\n";

		return board;
	}

}