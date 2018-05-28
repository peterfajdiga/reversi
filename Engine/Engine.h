#pragma once

#include <string>
#include "PlayerInterface.h"
#include "ViewInterface.h"
#include "HumanPlayer.h"

namespace reversi {

    /**
     * Engine
     *
     * Creates a game engine object for the Reversi game.
     *
     * Game engine must be connected to a view object using
     * the engine's setView method. View class must inherit
     * from the abstract ViewInterface class. The engine and
     * view communicate via a limited public API (see below,
     * also see ViewInterface.h).
     *
     * Example usage:
     *
     * reversi::Engine game;
     * reversi::ConcreteView view;
     *
     * game.setView(&view);
     * game.runGame();
     *
     */
    class Engine
    {
    public:
        Engine();
        virtual ~Engine();

        // setView
        // Saves a pointer to the instantiated view object.
        virtual void setView(ViewInterface* view);

        // runGame
        // Sets up a new game and starts the game loop.
        virtual void runGame();

        // getPlayer
        // Retrieves a player object (see PlayerInterface.h).
        // Will return a reference to the current player by default.
        // Set id to `1` or `2` to return player 1 or player 2 specifically.
        virtual PlayerInterface* getPlayer(int id = 0) const;

        // setPlayer
        // Updates a player object pointer, usually when changing player type.
        virtual void setPlayer(PlayerInterface* player, int id = 0);

        // positionStringToCoords
        // Resolves a string board position ("a1", "b2", etc.)
        // into board position x/y coordinates ({ 5, 6 }, etc.)
        // Will set the value of ints x and y to the coordinates matching
        // the position. Does not validate that a position is on the board.
        // Use isOnBoard to validate that a position is on the board.
        virtual void positionStringToCoords(const std::string& position, int& x, int& y);

        // positionCoordsToString
        // Resolves board position x/y coordinates ({ 5, 6 }, etc.)
        // into board positon string ("a1", "b2", etc.)
        virtual std::string positionCoordsToString(int x, int y);

        // isOnBoard
        // Determines if the supplied position (x/y indexes) is within the game board.
        virtual bool isOnBoard(int x, int y) const;

        // isOpen
        // Determines if the supplied position (x/y indexes) is open (is empty and not already taken).
        virtual bool isOpen(int x, int y) const;

        // isValidMove
        // Determines if the supplied position (x/y indexes) is a valid move
        // for the current player, i.e., it is on the board, the position is not already filled,
        // and it will flip at least one of the opponent's pieces.
        // Default behaviour will populate mPiecesToFlip with pointers to those board positions
        // that should have their values flipped by the move if it is valid.
        // Set isCheck to `true` to perform a faster check that determines that a move is valid
        // but does not find the complete set of pieces to flip for that move.
        virtual bool isValidMove(int x, int y, bool isCheck = false);

        // getPosition
        // Returns the value of the specified board position.
        // Possible values are `0` for an empty poistion,
        // `1` for Player 1's piece, and `2` for Player 2's piece.
        // If the position is not on the board, returns `-1`.
        // The game board is an 8x8 two-dimensional int array with x and y indexes
        // running from 0 to 7 starting from the top-left corner of the board.
        virtual int getPosition(int x, int y) const;

    protected:
        // setupGame
        // Initializes a new game, including board state and current player.
        // Calls view.setupGame.
        virtual void setupGame();

        // runGameLoop
        virtual void runGameLoop();

        // teardownGame
        // Calls view.teardownGame.
        virtual void teardownGame();

        // promptInput
        // Calls view.promptInput.
        virtual std::string promptInput(bool isGameOver);

        // updateState
        // Updates game state based on input.
        // Returns a Status enum value representing update status.
        // Position should be a string identifying a board position, e.g. "a1", "c5", etc.
        // The letter character denotes "x" position on board, from a-h, and can be upper- or lower-case.
        // The number character denotes "y" position on board, from 1-8.
        // "a1 is the top-left corner of the board. "h8" is the bottom right corner of the board.
        // The letter and number characters can be reversed, e.g. "5c" and "c5" are equivalent inputs.
        virtual Status updateState(const std::string& position);

        // displayStatus
        // Calls view.displayStatus.
        virtual void displayStatus(Status status, const std::string& input = "");

        // canMove
        // Determines if the current player can make a legal move.
        virtual bool canMove();

        // togglePlayer
        // Toggles mCurrentPlayer between `1` and `2`.
        virtual void togglePlayer();

        // initBoard
        // Initializes the game board to a new game state.
        virtual void initBoard();

        // initPiecesToFlip
        // Initializes the set of pieces to flip for a given valid move.
        virtual void initPiecesToFlip();

        // initPossiblePiecesToFlip
        // Initializes the set of pieces that are possibly flipped when evaluating
        // a position as a valid move.
        virtual void initPossiblePiecesToFlip();

        // flipPieces
        // Flips each piece in the set of pieces to flip for a given valid move.
        // This sets each identified position's value equal to the current player (`1` or `2`).
        virtual void flipPieces();

        // updateScores
        // Calculates each player's current score, and sets the score on each player object
        // using the player.setScore method.
        // To calculate final scores, where empty positions will be added to the winner's
        // total score, set isGameOver to `true`.
        virtual void updateScores(bool isGameOver = false);

        // setPosition
        // Sets the value of the supplied position (x/y indexes) to the supplied value.
        // Useful for testing, and can be used in a future version for loading a saved game.
        virtual void setPosition(int x, int y, int value);

    private:
        // Directions table used for finding valid moves.
        // Each table value is a vector (math vector, not a C++ STL data structure!)
        // representing one of the eight directions to check (up, up-right, right, etc.)
        static const int sDirectionsTable[8][2];

        // The maximum number of pieces to flip in a given direction is 6, but the
        // maximum number of positions that could be queued while searching is 8.
        static const int sMaxPossiblePiecesToFlipPerDirection = 8;

        static const int sMaxPiecesToFlipPerMove = 19;

        // The view reference must be set via setView before calling runGame.
        ViewInterface* mView;

        // Positions:
        // "a1" == mBoard[0][0]
        // "a2" == mBoard[0][1]
        // "b1" == mBoard[1][0]
        // "h8" == mBoard[7][7]
        int mBoard[8][8];

        PlayerInterface* mPlayer1;
        PlayerInterface* mPlayer2;

        // Current player is toggled between `1` and `2`.
        int mCurrentPlayer;

        // Temporary buffer for pieces flipped by a given move.
        int* mPiecesToFlip[sMaxPiecesToFlipPerMove];

        // Temporary buffer for pieces flipped in a given direction for a given move.
        int* mPossiblePiecesToFlip[sMaxPossiblePiecesToFlipPerDirection];

    };

}