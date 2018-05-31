#pragma once

#include <string>
#include "../PlayerInterface.h"
#include "../ViewInterface.h"
#include "../Engine.h"


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

        EasyComputerPlayer(const std::string& name);

        ~EasyComputerPlayer() override;

        Tile getMove(const Board& board, ViewInterface& view) override;
    };

}
