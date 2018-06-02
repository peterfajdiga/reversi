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
    public:
        Engine();
        virtual ~Engine();

        // setView
        // Saves a pointer to the instantiated view object.
        virtual void setView(ViewInterface* view);

        // runGame
        // Sets up a new game and starts the game loop.
        virtual void runGame();

        virtual void quitGame();

        virtual void newGame();

        // replace current player with an AI player
        template <class T>
        void playerToAi() {
            //assert(!board.isGameOver());
            const color currentPlayerColor = board.getCurrentPlayer();
            PlayerInterface*& currentPlayer = currentPlayerColor == white ? playerWhite : playerBlack;
            delete currentPlayer;
            currentPlayer = new T(currentPlayerColor);
        }

        // getPlayer
        // Retrieves a player object (see PlayerInterface.h).
        // Will return a reference to the current player by default.
        virtual PlayerInterface* getPlayer(color playerId = unoccupied) const;

        virtual const Board& getBoard() const;

        virtual const Tile& getLastMoveTile() const;

        virtual const PlayerInterface* getLastMovePlayer() const;

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

        // updateState
        // Updates game state based on input.
        // Returns a Status enum value representing update status.
        virtual Status updateState(const Tile& move);

        // displayStatus
        // Calls view.displayStatus.
        virtual void displayStatus(Status status);

    private:

        bool playCurrentGame, playNextGame;

        // The view reference must be set via setView before calling runGame.
        ViewInterface* mView;

        // Positions:
        Board board;

        bool lastMoveSkipped;
        Tile lastMoveTile;  // if lastMoveSkipped, think of this as lastLastMoveTile
        color lastMovePlayer;  // if lastMoveSkipped, think of this as lastLastMovePlayer

        PlayerInterface* playerWhite;
        PlayerInterface* playerBlack;

    };

}
