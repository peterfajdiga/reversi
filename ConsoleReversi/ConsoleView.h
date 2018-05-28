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

        void setupGame(Engine& engine) override;

        void teardownGame(Engine& engine) override;

        std::string promptInput(Engine& engine, bool isGameOver) override;

        void displayStatus(Engine& engine, Status status, const std::string& input = "") override;

    protected:
        // HELPERS

        virtual std::string drawBoard(const Engine& engine);
        virtual std::string drawScore(const Engine& engine);
    };

}
