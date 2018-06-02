#pragma once

#include "AiPlayerTimed.h"


namespace reversi {

    /**
    * EasyComputerPlayer
    *
    * Concrete player class for easy computer players.
    *
    */
    class EasyComputerPlayer : public AiPlayerTimed {
    public:
        EasyComputerPlayer();

        EasyComputerPlayer(const std::string& name);

        ~EasyComputerPlayer() override;

        Tile getMoveTimed(const Board& board) override;
    };

}
