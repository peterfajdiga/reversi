#include "Engine.h"
#include "Tile.h"


namespace reversi {

    const int Engine::sDirectionsTable[8][2] = {
        // { x, y }
        { 0, 1 },    // up
        { 1, 1 },    // up-left
        { 1, 0 },    // left
        { 1, -1 },    // down-left
        { 0, -1 },    // down
        { -1, -1 },    // down-right
        { -1, 0 },    // right
        { -1, 1 }    // up-right
    };


    Engine::Engine() {
        mCurrentPlayer = 1;

        // set initial players as Human
        mPlayer1 = new HumanPlayer;
        mPlayer1->setId(1);

        mPlayer2 = new HumanPlayer;
        mPlayer2->setId(2);
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
        initBoard();
        updateScores();

        mCurrentPlayer = 1;

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
            case 113:  // q: Quit
                isGameRunning = false;
                displayStatus(Status::QUIT);
                break;

            case 110:  // n: New Game
                isGameOver = false;
                isLastMovePass = false;
                teardownGame();
                setupGame();
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
        if (!isOnBoard(move)) {
            // position is outside of the board
            return Status::OUT_OF_BOUNDS;
        }

        // check empty position
        if (!isOpen(move)) {
            // position is already filled
            return Status::POSITION_FILLED;
        }

        // check valid move
        if (!isValidMove(move, false)) {
            // position must flip at least one of the opponent player's pieces
            return Status::INVALID_MOVE;
        }

        mBoard[move.x][move.y] = mCurrentPlayer;
        flipPieces();
        updateScores();

        return Status::SUCCESS;
    }


    void Engine::displayStatus(Status status, const std::string& input) {
        mView->displayStatus(*this, status, input);
    }


    void Engine::initBoard() {
        int i, j;

        // initialize each position to empty
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 8; j++) {
                mBoard[i][j] = 0;
            }
        }

        // initialize starting positions for each player
        mBoard[3][3] = 2;
        mBoard[3][4] = 1;
        mBoard[4][3] = 1;
        mBoard[4][4] = 2;
    }


    PlayerInterface* Engine::getPlayer(int id) const {
        if (id == 0) {
            id = mCurrentPlayer;
        }

        if (id == 1) {
            return mPlayer1;
        }

        return mPlayer2;
    }


    void Engine::setPlayer(PlayerInterface* player, int id) {
        if (id == 0) {
            id = mCurrentPlayer;
        }

        if (id == 1) {
            delete mPlayer1;
            mPlayer1 = player;
        }
        else if (id == 2) {
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
                if (isOpen(move) && isValidMove(move, true)) {
                    return true;
                }
            }
        }

        return false;
    }

    void Engine::togglePlayer() {
        // bitwise xor with 3 will toggle between 1 and 2
        mCurrentPlayer ^= 3;
    }


    bool Engine::isOnBoard(const Tile& move) const {
        return move.x >= 0 && move.x <= 7 && move.y >= 0 && move.y <= 7;
    }


    bool Engine::isOpen(const Tile& move) const {
        return mBoard[move.x][move.y] == 0;
    }


    bool Engine::isValidMove(const Tile& move, bool isCheck) {
        int i, j, xStep, yStep, flipCount = 0;

        initPiecesToFlip();

        // for each direction from the piece position
        // look for one or more adjacent pieces of the opposing player
        // followed by a piece of this player
        // max of 7 steps can be taken in any given direction
        // take 8 steps so that the last check is off the board
        // and will clear mPossiblePiecesToFlip if we get there
        for (i = 0; i < 8; i++) {
            // init position and step
            Tile i_move(move);
            xStep = sDirectionsTable[i][0];
            yStep = sDirectionsTable[i][1];

            // short-circuit search based on proximity to edge and direction vector
            // e.g. a position in the first two rows of the board does not need to
            // search in the up-right, up, or up-left directions (yStep = 1) because
            // no pieces can be flipped in that direction
            // yStep is inverted with respect to board array index
            if (move.y < 2 && yStep == 1 || move.y > 5 && yStep == -1 || move.x < 2 && xStep == -1 || move.x > 5 && xStep == 1) {
                continue;
            }

            initPossiblePiecesToFlip();

            // max of 7 steps can be taken in any given direction
            // take 8 steps so that the last check is off the board
            // and will clear mPossiblePiecesToFlip if we get there
            for (j = 0; j < 8; j++) {
                // apply step
                // step is represented as a math vector
                // yStep is inverted with respect to board array index
                i_move.x += xStep;
                i_move.y -= yStep;

                // check bounds and empty position
                if (!isOnBoard(i_move) || isOpen(i_move)) {
                    // no flipped pieces in this direction
                    initPossiblePiecesToFlip();

                    // stop searching in this direction
                    break;
                }

                // check for own piece
                if (mBoard[i_move.x][i_move.y] == mCurrentPlayer) {
                    // stop searching in this direction
                    break;
                }

                // found opposing piece
                // save a reference to this piece
                // and continue searching in this direction
                mPossiblePiecesToFlip[j] = &mBoard[i_move.x][i_move.y];
            }

            for (j = 0; j < sMaxPossiblePiecesToFlipPerDirection; j++) {
                if (mPossiblePiecesToFlip[j] == NULL) {
                    break;
                }

                // at this point, the position is a valid move
                // stop searching if isCheck is `true`
                if (isCheck) {
                    return true;
                }

                // save reference to flippable piece
                // increment flipCount
                mPiecesToFlip[flipCount++] = mPossiblePiecesToFlip[j];
            }
        }

        if (flipCount > 0) {
            // if any of the opponent's pieces will be flipped, it's a valid move
            return true;
        }

        return false;
    }


    void Engine::initPiecesToFlip() {
        int i;

        for (i = 0; i < sMaxPiecesToFlipPerMove; i++) {
            mPiecesToFlip[i] = NULL;
        }
    }


    void Engine::initPossiblePiecesToFlip() {
        int i;

        for (i = 0; i < sMaxPossiblePiecesToFlipPerDirection; i++) {
            mPossiblePiecesToFlip[i] = NULL;
        }
    }


    void Engine::flipPieces() {
        int i;

        for (i = 0; i < sMaxPiecesToFlipPerMove; i++) {
            if (mPiecesToFlip[i] == NULL) {
                break;
            }

            *mPiecesToFlip[i] = mCurrentPlayer;
        }
    }


    void Engine::updateScores(bool isGameOver) {
        int i, j, s1 = 0, s2 = 0;

        for (j = 0; j < 8; j++) {
            for (i = 0; i < 8; i++) {
                switch (mBoard[i][j]) {
                case 1:
                    s1 += 1;
                    break;
                case 2:
                    s2 += 1;
                    break;
                }
            }
        }

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

    int Engine::getPosition(const Tile& move) const {
        if (isOnBoard(move)) {
            return mBoard[move.x][move.y];
        }

        return -1;
    }


    void Engine::setPosition(const Tile& move, int value) {
        if (isOnBoard(move)) {
            mBoard[move.x][move.y] = value;
        }
    }

}
