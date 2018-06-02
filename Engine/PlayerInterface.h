#pragma once

#include <string>
#include "ViewInterface.h"
#include "constants.h"
#include "Containers/Board.h"

namespace reversi {

    /**
     * PlayerInterface
     *
     * Abstract class to organize player data.
     *
     * Concrete player classes must implement the promptInput method.
     * HumanPlayer is implemented and is the initial player type.
     *
     * Game view may access player objects via engine.getPlayer(id).
     *
     */
    class PlayerInterface
    {
    public:
        PlayerInterface(color playerColor);

        PlayerInterface(color playerColor, const std::string& name);

        virtual ~PlayerInterface();

        virtual Tile getMove(const Board& board, ViewInterface& view) = 0;

        const color playerColor;

        const std::string name;
    };

}
