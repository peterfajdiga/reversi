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

        std::string promptInput(bool isGameOver) override;

        void displayStatus(Status status, const std::string& input) override;

    protected:
        // HELPERS

        virtual std::string drawBoard(const Board &board) const;
        virtual std::string drawScore() const;
        virtual std::string getFormattedName(const PlayerInterface& player) const;
    };

}
