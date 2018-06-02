#pragma once

#include "AiPlayerTimed.h"


namespace reversi {

    class MonteCarloPlayer : public AiPlayerTimed {
    public:
        MonteCarloPlayer();

        MonteCarloPlayer(const std::string& name);

        ~MonteCarloPlayer() override;

        Tile getMoveTimed(const Board& board) override;

        double sampleMC(const Board& board) const;

        bool playRandom(const Board& boardStart) const;
    };

}
