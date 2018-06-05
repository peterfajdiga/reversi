#pragma once

#include <string>
#include "../Engine/Engine.h"

namespace reversi {

    /**
     * ConsoleView
     *
     * Concrete console view class for Engine.
     *
     * Inherits from ViewInterface and implements the public
     * pure virtual interface methods.
     *
     * Displays a simple text-based Reversi game.
     *
     */
    class ConsoleView : public ViewInterface {
    public:
        ConsoleView();

        ~ConsoleView() override;

        // INTERFACE FOR ViewInterface

        void setupGame() override;

        void teardownGame() override;

        void displayState(bool isGameOver) override;

        Tile getMoveInput() override;

        void onGameOver() override;

        void displayStatus(Status status) override;

    protected:
        // HELPERS

        virtual std::string drawBoard(const Board& board, bool highlight=false) const;
        virtual std::string drawScore() const;
        virtual std::string getFormattedName(const PlayerInterface& player) const;
        virtual void selectAi() const;
    };

}
