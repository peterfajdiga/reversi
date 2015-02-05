#pragma once

#include <string>
#include "../ReversiGameEngine/Engine.h"


/**
 * ReversiGameConsoleView
 *
 * Concrete console view class for ReversiGameEngine.
 *
 * Inherits from ReversiGameView and implements the public
 * pure virtual interface methods.
 *
 * Displays a simple text-based Reversi game.
 *
 */
class ReversiGameConsoleView : public ReversiGameView
{
public:
	ReversiGameConsoleView();
	virtual ~ReversiGameConsoleView();

	// INTERFACE FOR ReversiGameView

	virtual void setupGame(const ReversiGameEngine& engine);
	virtual void teardownGame(const ReversiGameEngine& engine);
	virtual std::string promptInput(const ReversiGameEngine& engine, bool isGameOver);
	virtual void displayStatus(const ReversiGameEngine& engine, ReversiGameStatus status, const std::string& input = "");

protected:
	// HELPERS

	virtual std::string drawBoard(const ReversiGameEngine& engine);
};