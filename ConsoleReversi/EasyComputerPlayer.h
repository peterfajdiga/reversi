#pragma once

#include <string>
#include "../Engine/PlayerInterface.h"
#include "../Engine/ViewInterface.h"
#include "../Engine/Engine.h"


namespace reversi {

    /**
    * EasyComputerPlayer
    *
    * Concrete player class for easy computer players.
    *
    */
    class EasyComputerPlayer : public PlayerInterface {
    public:
        EasyComputerPlayer();

        ~EasyComputerPlayer() override;

        std::string promptInput(Engine& engine, ViewInterface& view, bool isGameOver = false) override;

        std::string generateName() override;

    private:
        virtual std::string getMove(Engine& engine);
    };

}
