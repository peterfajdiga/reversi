#include "Engine.h"
#include "Containers/Tile.h"
#include "constants.h"
#include "Ai/EasyComputerPlayer.h"

namespace reversi {


    Engine::Engine() {
        playerWhite = new HumanPlayer(white);
        playerBlack = new HumanPlayer(black);
    }


    Engine::~Engine() {
        // set view pointer to NULL
        mView = nullptr;

        // delete players
        delete playerWhite;
        delete playerBlack;
    }


    void Engine::setView(ViewInterface* view) {
        mView = view;
        view->engine = this;
    }



    void Engine::runGame() {
        playNextGame = true;
        while (playNextGame) {
            playNextGame = false;
            setupGame();
            runGameLoop();
            teardownGame();
        }
    }

    void Engine::quitGame() {
        playCurrentGame = false;
    }

    void Engine::newGame() {
        quitGame();
        playNextGame = true;
    }


    void Engine::setupGame() {
        board = Board();  // TODO: do differently
        mView->setupGame();
    }


    void Engine::runGameLoop() {
        playCurrentGame = true;
        while (playCurrentGame) {
            bool isGameOver = board.isGameOver();
            mView->displayState(isGameOver);

            if (isGameOver) {
                mView->onGameOver();
                break;
            }

            try {
                Tile requestedMove = getPlayer()->getMove(board, *mView);  // TODO: reference

                Status status = updateState(requestedMove);
                displayStatus(status);
                if (lastMoveSkipped) {
                    displayStatus(Status::CANNOT_MOVE);
                }
            } catch (const NoMoveException& e) {
                continue;
            }
        }
    }


    void Engine::teardownGame() {
        mView->teardownGame();
    }


    Status Engine::updateState(const Tile& move) {
        const color currentPlayer = board.getCurrentPlayer();

        // check bounds
        if (!move.isOnBoard()) {
            // position is outside of the board
            return Status::OUT_OF_BOUNDS;
        }

        // check empty position
        if (!board.isOpen(move)) {
            // position is already filled
            return Status::POSITION_FILLED;
        }

        try {
            lastMoveSkipped = board.doMove(move);
            lastMovePlayer = currentPlayer;
            lastMoveTile = move;
        } catch (const InvalidMoveException& e) {
            return Status::INVALID_MOVE;
        }

        return Status::SUCCESS;
    }


    void Engine::displayStatus(Status status) {
        mView->displayStatus(status);
    }


    PlayerInterface* Engine::getPlayer(color playerId) const {
        if (playerId == 0) {
            playerId = board.getCurrentPlayer();
        }
        return playerId == white ? playerWhite : playerBlack;
    }


    const Board& Engine::getBoard() const {
        return board;
    }


    const Tile& Engine::getLastMoveTile() const {
        return lastMoveTile;
    }

    const PlayerInterface* Engine::getLastMovePlayer() const {
        return getPlayer(lastMovePlayer);
    }

}
