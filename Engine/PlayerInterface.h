#pragma once

#include <string>
#include "ViewInterface.h"
#include "constants.h"
#include "Containers/Board.h"

namespace reversi {

    class Engine; // forward declaration

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
        friend class Engine;

    public:
        PlayerInterface();

        PlayerInterface(const std::string& name);

        virtual ~PlayerInterface();

        virtual color getId() const;

        virtual Tile getMove(const Board& board, ViewInterface& view) = 0;

        const std::string name;

    private:
        color mId;
    };

}
