#pragma once

#include <string>
#include "../PlayerInterface.h"

namespace reversi {

    class MonteCarloPlayer : public PlayerInterface {
    public:
        MonteCarloPlayer();

        MonteCarloPlayer(const std::string& name);

        ~MonteCarloPlayer() override;

        Tile getMove(const Board& board, ViewInterface& view) override;

        double sampleMC(const Board& board) const;

        bool playRandom(const Board& boardStart) const;
    };

}
