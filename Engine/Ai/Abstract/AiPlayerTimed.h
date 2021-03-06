#pragma once

#include "../../PlayerInterface.h"


namespace reversi {

    class AiPlayerTimed : public PlayerInterface {
    public:
        AiPlayerTimed(color playerColor);

        AiPlayerTimed(color playerColor, const std::string& name);

        ~AiPlayerTimed() override;

        Tile getMove(const Board& board, const std::vector<Tile>& moveHistory, ViewInterface& view) final;

        virtual Tile getMoveTimed(const Board& board, const std::vector<Tile>& moveHistory) = 0;

        clock_t getCpuTime() const;

    private:
        clock_t cpuTime;
    };

}
