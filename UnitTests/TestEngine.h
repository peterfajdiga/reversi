#pragma once

#include <string>
#include "../ReversiGameEngine/Engine.h"


namespace reversi {

	/**
	 * TestEngine
	 *
	 * Exposes most class methods to public access control for test purposes.
	 *
	 */
	class TestEngine : public Engine
	{
	public:
		TestEngine();
		virtual ~TestEngine();

		// expose protected Engine methods

		Status updateState(const std::string& position);
		virtual bool canMove();
		virtual void togglePlayer();
		virtual void initBoard();
		virtual void initPiecesToFlip();
		virtual void initPossiblePiecesToFlip();
		virtual void flipPieces();
		virtual void updateScores(bool isGameOver = false);
		virtual void setPosition(int x, int y, int value);

		// helpers

		virtual void clearBoard();
	};

}