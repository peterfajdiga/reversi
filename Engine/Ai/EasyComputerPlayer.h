#pragma once

#include "Abstract/AiPlayerTimed.h"


namespace reversi {

    /**
    * EasyComputerPlayer
    *
    * Concrete player class for easy computer players.
    *
    */
    class EasyComputerPlayer : public AiPlayerTimed {
    public:
        EasyComputerPlayer(color playerColor);

        EasyComputerPlayer(color playerColor, const std::string& name);

        ~EasyComputerPlayer() override;

        Tile getMoveTimed(const Board& board, const std::vector<Tile>& moveHistory) override;
    };

}
