#include "TestEngine.h"


namespace reversi {

    TestEngine::TestEngine()
    {

    }


    TestEngine::~TestEngine()
    {

    }


    void TestEngine::clearBoard()
    {
        initBoard();
        setPosition(3, 3, 0);
        setPosition(3, 4, 0);
        setPosition(4, 3, 0);
        setPosition(4, 4, 0);
    }


    Status TestEngine::updateState(const std::string& position)
    {
        return Engine::updateState(position);
    }


    bool TestEngine::canMove()
    {
        return Engine::canMove();
    }


    void TestEngine::togglePlayer()
    {
        return Engine::togglePlayer();
    }


    void TestEngine::initBoard()
    {
        return Engine::initBoard();
    }


    void TestEngine::initPiecesToFlip()
    {
        return Engine::initPiecesToFlip();
    }


    void TestEngine::initPossiblePiecesToFlip()
    {
        return Engine::initPossiblePiecesToFlip();
    }


    void TestEngine::flipPieces()
    {
        return Engine::flipPieces();
    }


    void TestEngine::updateScores(bool isGameOver)
    {
        return Engine::updateScores(isGameOver);
    }


    void TestEngine::setPosition(int x, int y, int value)
    {
        return Engine::setPosition(x, y, value);
    }

}