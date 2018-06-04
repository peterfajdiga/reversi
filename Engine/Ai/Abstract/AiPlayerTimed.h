#pragma once

#include <ctime>
#include "../../PlayerInterface.h"


namespace reversi {

    class AiPlayerTimed : public PlayerInterface {
    public:
        AiPlayerTimed(color playerColor);

        AiPlayerTimed(color playerColor, const std::string& name);

        ~AiPlayerTimed() override;

        Tile getMove(const Board& board, ViewInterface& view) final;

        virtual Tile getMoveTimed(const Board& board) = 0;

        clock_t getCpuTime() const;

    private:
        clock_t cpuTime;
    };

}
