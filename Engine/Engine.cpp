#include "Engine.h"
#include "Containers/Tile.h"
#include "constants.h"

namespace reversi {


    Engine::Engine(PlayerInterface* player1, PlayerInterface* player2) : mPlayer1(player1), mPlayer2(player2) {
        mPlayer1->mId = white;
        mPlayer2->mId = black;
        mCurrentPlayer = white;
    }


    Engine::~Engine() {
        // set view pointer to NULL
        mView = NULL;

        // delete players
        delete mPlayer1;
        delete mPlayer2;
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
        updateScores();

        mCurrentPlayer = white;

        mView->setupGame(*this);
    }


    void Engine::runGameLoop() {
        bool isGameRunning = true, isGameOver = false, isLastMovePass = false, isPlayerAbleToMove;
        std::string input;
        char i0;  // first character of input
        Status status;

        bool isNewState = true;

        while (isGameRunning) {
            isPlayerAbleToMove = canMove();

            // is game over?
            if (isLastMovePass && !isPlayerAbleToMove) {
                isGameOver = true;
                updateScores(true);
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
                    status = updateState(input);
                    displayStatus(status, input);

                    if (status == Status::SUCCESS) {
                        isLastMovePass = false;
                        togglePlayer();
                        isNewState = true;
                    }
                }
                else {
                    displayStatus(Status::CANNOT_MOVE);
                    isLastMovePass = true;
                    togglePlayer();
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

        // check valid move
        if (!board.isValidMovePerform(move, mCurrentPlayer)) {
            // position must flip at least one of the opponent player's pieces
            return Status::INVALID_MOVE;
        }

        board[move] = mCurrentPlayer;
        board.flipPieces(mCurrentPlayer);
        updateScores();

        return Status::SUCCESS;
    }


    void Engine::displayStatus(Status status, const std::string& input) {
        mView->displayStatus(*this, status, input);
    }


    PlayerInterface* Engine::getPlayer(color playerId) const {
        if (playerId == 0) {
            playerId = mCurrentPlayer;
        }
        return playerId == 1 ? mPlayer1 : mPlayer2;
    }


    const Board& Engine::getBoard() const {
        return board;
    }


    void Engine::setPlayer(PlayerInterface* player, color playerId) {
        player->mId = getPlayer()->mId;

        if (playerId == 0) {
            playerId = mCurrentPlayer;
        }

        if (playerId == 1) {
            delete mPlayer1;
            mPlayer1 = player;
        }
        else if (playerId == 2) {
            delete mPlayer2;
            mPlayer2 = player;
        }
    }


    bool Engine::canMove() {
        // check each position on the board
        // to see if it is a valid move for this player
        // stop searching when a valid move is found
        for (Tile move(0, 0); move.y < 8; move.y++) {
            for (move.x = 0; move.x < 8; move.x++) {
                // check open position and valid move
                // set isCheck flag to shorten isValidMove search
                if (board.isOpen(move) && board.isValidMove(move, mCurrentPlayer)) {
                    return true;
                }
            }
        }

        return false;
    }

    void Engine::togglePlayer() {
        // bitwise xor with 3 will toggle between 1 and 2
        mCurrentPlayer = (color)(mCurrentPlayer ^ 3);
    }


    void Engine::updateScores(bool isGameOver) {
        score s1 = board.getScore(white);
        score s2 = board.getScore(black);

        if (isGameOver) {
            if (s1 > s2 || s2 > s1) {
                // if one player wins
                // add all the empty positions to the winner's score
                (s1 > s2 ? s1 : s2) += (64 - s2 - s1);
            }

            // don't modify scores in case of a tie
        }

        mPlayer1->setScore(s1);
        mPlayer2->setScore(s2);
    }

}
