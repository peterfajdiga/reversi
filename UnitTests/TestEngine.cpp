#include "TestEngine.h"


ReversiGameTestEngine::ReversiGameTestEngine()
{

}


ReversiGameTestEngine::~ReversiGameTestEngine()
{

}


void ReversiGameTestEngine::clearBoard()
{
	initBoard();
	setPosition(3, 3, 0);
	setPosition(3, 4, 0);
	setPosition(4, 3, 0);
	setPosition(4, 4, 0);
}


ReversiGameStatus ReversiGameTestEngine::updateState(const std::string& position)
{
	return ReversiGameEngine::updateState(position);
}


bool ReversiGameTestEngine::canMove()
{
	return ReversiGameEngine::canMove();
}


void ReversiGameTestEngine::togglePlayer()
{
	return ReversiGameEngine::togglePlayer();
}


void ReversiGameTestEngine::initBoard()
{
	return ReversiGameEngine::initBoard();
}


void ReversiGameTestEngine::initPiecesToFlip()
{
	return ReversiGameEngine::initPiecesToFlip();
}


void ReversiGameTestEngine::initPossiblePiecesToFlip()
{
	return ReversiGameEngine::initPossiblePiecesToFlip();
}


void ReversiGameTestEngine::flipPieces()
{
	return ReversiGameEngine::flipPieces();
}


void ReversiGameTestEngine::updateScores(bool isGameOver)
{
	return ReversiGameEngine::updateScores(isGameOver);
}


void ReversiGameTestEngine::setPosition(int x, int y, int value)
{
	return ReversiGameEngine::setPosition(x, y, value);
}
