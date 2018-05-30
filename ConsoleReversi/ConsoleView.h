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

        void setupGame(const Engine& engine) override;

        void teardownGame(const Engine& engine) override;

        void displayState(const Engine& engine, bool isGameOver) override;

        std::string promptInput(Engine& engine, bool isGameOver) override;

        void displayStatus(const Engine& engine, Status status, const std::string& input = "") override;

    protected:
        // HELPERS

        virtual std::string drawBoard(const Engine& engine) const;
        virtual std::string drawScore(const Engine& engine) const;
        virtual std::string getFormattedName(const PlayerInterface& player) const;
    };

}
