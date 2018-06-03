#pragma once

#include "MonteCarloPlayer.h"


namespace reversi {

    class MonteCarloTreePlayer : public MonteCarloPlayer {
    public:
        MonteCarloTreePlayer(color playerColor);

        MonteCarloTreePlayer(color playerColor, const std::string& name);

        ~MonteCarloTreePlayer() override;

        Tile getMoveTimed(const Board& board) override;
    };

}
