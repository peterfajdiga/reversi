#pragma once

#include "../PlayerInterface.h"


namespace reversi {

    class AiPlayerTimed : public PlayerInterface {
    public:
        AiPlayerTimed();

        AiPlayerTimed(const std::string& name);

        ~AiPlayerTimed() override;

        Tile getMove(const Board& board, ViewInterface& view) final;

        virtual Tile getMoveTimed(const Board& board) = 0;
    };

}
