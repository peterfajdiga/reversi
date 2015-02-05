#pragma once

#include <string>
#include "../Engine/Engine.h"

namespace reversi {

	/**
	 * ConsoleView
	 *
	 * Concrete console view class for Engine.
	 *
	 * Inherits from ViewInterface and implements the public
	 * pure virtual interface methods.
	 *
	 * Displays a simple text-based Reversi game.
	 *
	 */
	class ConsoleView : public ViewInterface
	{
	public:
		ConsoleView();
		virtual ~ConsoleView();

		// INTERFACE FOR ViewInterface

		virtual void setupGame(const Engine& engine);
		virtual void teardownGame(const Engine& engine);
		virtual std::string promptInput(const Engine& engine, bool isGameOver);
		virtual void displayStatus(const Engine& engine, Status status, const std::string& input = "");

	protected:
		// HELPERS

		virtual std::string drawBoard(const Engine& engine);
	};

}