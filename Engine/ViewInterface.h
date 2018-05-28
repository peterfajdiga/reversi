#pragma once

#include <string>

namespace reversi {

    class Engine; // forward declaration


    /**
     * Status
     *
     * Enumerated game status values passed to the displayStatus method.
     *
     */
    enum Status {
        SUCCESS,            // valid move, piece successfully placed
        OUT_OF_BOUNDS,        // invalid move, position is not on the board
        POSITION_FILLED,    // invalid move, position is already filled
        INVALID_MOVE,        // invalid move, position would not flip any of the opponent's pieces
        CANNOT_MOVE,        // current player cannot move
        QUIT,                // quit application
        FINDING_MOVE        // searching for a computer player's move
    };


    /**
     * ViewInterface
     *
     * Abstract base class for game view.
     *
     * Concrete game view class must inherit from this class.
     *
     * Each interface method is passed a reference to the
     * game engine. See Engine.h for public view helper
     * methods accessible from this reference.
     *
     */
    class ViewInterface
    {
    public:
        ViewInterface();
        virtual ~ViewInterface();

        // setupGame
        // Called before a new game is started.
        // Automatically called when the game loop itself starts.
        // Typically used to display welcome and instructions before the new game.
        virtual void setupGame(Engine& engine) = 0;

        // teardownGame
        // Called after a game ends, as the game loop itself ends
        // or just before a new game is setup.
        virtual void teardownGame(Engine& engine) = 0;

        // promptInput
        // Displays the game board and prompts for player input.
        // Input string can match a special character recognized by the
        // game loop ('n' for New Game, 'q' for Quit) or will be treated as
        // a position on the board for a possible move by the current player.
        virtual std::string promptInput(Engine& engine, bool isGameOver) = 0;

        // displayStatus
        // Displays the game status, usually informing the current player
        // of an invalid move, or that they cannot move.
        // See enumerated Status values above.
        virtual void displayStatus(Engine& engine, Status status, const std::string& input = "") = 0;
    };

}