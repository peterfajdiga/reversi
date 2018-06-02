#pragma once

#include <string>
#include "PlayerInterface.h"

namespace reversi {

    /**
    * HumanPlayer
    *
    * Concrete player class for human players.
    *
    */
    class HumanPlayer : public PlayerInterface {
    public:
        HumanPlayer(color playerColor);

        HumanPlayer(color playerColor, const std::string& name);

        virtual ~HumanPlayer();

        Tile getMove(const Board& board, ViewInterface& view) override;
    };

}
