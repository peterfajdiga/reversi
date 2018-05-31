#include "Engine.h"
#include "Containers/Tile.h"
#include "constants.h"

namespace reversi {


    Engine::Engine() {
        playerWhite = new HumanPlayer();
        playerBlack = new HumanPlayer();
        playerWhite->mId = white;
        playerBlack->mId = black;
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
    }



    void Engine::runGame() {
        setupGame();
        runGameLoop();
        teardownGame();
    }


    void Engine::setupGame() {
        board = Board();  // TODO: do differently
        mView->setupGame(*this);
    }


    void Engine::runGameLoop() {
        bool isGameRunning = true, isGameOver = false, isLastMovePass = false, isPlayerAbleToMove;
        std::string input;
        char i0;  // first character of input
        Status status;

        bool isNewState = true;

        while (isGameRunning) {
            isPlayerAbleToMove = board.canMove();

            // is game over?
            if (isLastMovePass && !isPlayerAbleToMove) {
                isGameOver = true;
            }

            // prompt for input
            if (!isPlayerAbleToMove && !isGameOver) {
                // don't ask for input if the player can't move but the game is not over
                input = " ";
            }
            else {
                if (isNewState) {
                    mView->displayState(*this, isGameOver);
                    isNewState = false;
                }
                input = promptInput(isGameOver);
            }

            i0 = tolower(input[0]);

            // evaluate the first character of input looking for special actions
            // note that special actions should only be defined for letters after "h"
            switch (i0) {
            case 'q':  // q: Quit
                isGameRunning = false;
                displayStatus(Status::QUIT);
                break;

            case 'n':  // n: New Game
                isGameOver = false;
                isLastMovePass = false;
                teardownGame();
                setupGame();
                isNewState = true;
                break;

            default:
                if (isPlayerAbleToMove) {
                    status = updateState(input);  // do move
                    displayStatus(status, input);

                    if (status == Status::SUCCESS) {
                        isLastMovePass = false;
                        isNewState = true;
                    }
                }
                else {
                    displayStatus(Status::CANNOT_MOVE);
                    isLastMovePass = true;
                    board.doNothing();  // skip move
                }
            }
        }
    }


    void Engine::teardownGame() {
        mView->teardownGame(*this);
    }


    std::string Engine::promptInput(bool isGameOver) {
        return getPlayer()->promptInput(*this, *mView, isGameOver);
    }


    Status Engine::updateState(const std::string& position) {
        Tile move(position);

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
            board.doMove(move);
        } catch (InvalidMoveException& e) {
            return Status::INVALID_MOVE;
        }

        return Status::SUCCESS;
    }


    void Engine::displayStatus(Status status, const std::string& input) {
        mView->displayStatus(*this, status, input);
    }


    PlayerInterface* Engine::getPlayer(color playerId) const {
        if (playerId == 0) {
            playerId = board.getCurrentPlayer();
        }
        return playerId == 1 ? playerWhite : playerBlack;
    }


    const Board& Engine::getBoard() const {
        return board;
    }


    void Engine::setPlayer(PlayerInterface* player, color playerId) {  // TODO: remove (along with ability to change player to ai)
        player->mId = getPlayer()->mId;

        if (playerId == 0) {
            playerId = board.getCurrentPlayer();
        }

        if (playerId == 1) {
            delete playerWhite;
            playerWhite = player;
        }
        else if (playerId == 2) {
            delete playerBlack;
            playerBlack = player;
        }
    }

}
