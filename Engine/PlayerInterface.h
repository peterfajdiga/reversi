#pragma once

#include <ctime>
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
    class PlayerInterface {
    public:
        PlayerInterface(color playerColor);

        PlayerInterface(color playerColor, const std::string& name);

        virtual ~PlayerInterface();

        virtual Tile getMove(const Board& board, const std::vector<Tile>& moveHistory, ViewInterface& view) = 0;

        color playerColor;  // not const for pid  // TODO: make const in release

        const std::string name;

        static const clock_t MOVE_TIME = (clock_t)(0.1 * CLOCKS_PER_SEC);
    };

}
