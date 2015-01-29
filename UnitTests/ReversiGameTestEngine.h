#pragma once

#include <string>
#include "../ReversiGameEngine/ReversiGameEngine.h"


/**
 * ReversiGameTestEngine
 *
 * Exposes most class methods to public access control for test purposes.
 *
 */
class ReversiGameTestEngine : public ReversiGameEngine
{
public:
	ReversiGameTestEngine();
	virtual ~ReversiGameTestEngine();

	// expose ReversiGameEngine methods

	ReversiGameStatus updateState(const std::string& position);
	virtual bool canMove();
	virtual void togglePlayer();
	virtual void initBoard();
	virtual bool isOnBoard(int x, int y) const;
	virtual bool isValidMove(int x, int y, bool isCheck = false);
	virtual void initPiecesToFlip();
	virtual void initPossiblePiecesToFlip();
	virtual void flipPieces();
	virtual void updateScores(bool isGameOver = false);
	virtual void setPosition(int x, int y, int value);

	// helpers

	virtual void clearBoard();
};