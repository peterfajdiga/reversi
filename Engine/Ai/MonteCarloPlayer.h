#pragma once

#include "Abstract/AiPlayerTimed.h"


namespace reversi {

    class MonteCarloPlayer : public AiPlayerTimed {
    public:
        MonteCarloPlayer(color playerColor);

        MonteCarloPlayer(color playerColor, const std::string& name);

        ~MonteCarloPlayer() override;

        Tile getMoveTimed(const Board& board) override;

        bool playRandom(const Board& boardStart) const;
    };

}
