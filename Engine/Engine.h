#pragma once

#include <string>
#include "PlayerInterface.h"
#include "ViewInterface.h"
#include "HumanPlayer.h"
#include "Containers/Tile.h"
#include "constants.h"
#include "Containers/Board.h"

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
    class Engine {
        friend class EasyComputerPlayer;  // TODO: remove
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
        virtual PlayerInterface* getPlayer(color playerId = unoccupied) const;

        // setPlayer
        // Updates a player object pointer, usually when changing player type.
        virtual void setPlayer(PlayerInterface* player, color playerId = unoccupied);

        virtual const Board& getBoard() const;

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

    private:

        // The view reference must be set via setView before calling runGame.
        ViewInterface* mView;

        // Positions:
        Board board;

        PlayerInterface* playerWhite;
        PlayerInterface* playerBlack;

    };

}
