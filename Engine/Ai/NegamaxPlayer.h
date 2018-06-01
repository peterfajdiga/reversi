#pragma once

#include "../PlayerInterface.h"


namespace reversi {

    class NegamaxPlayer : public PlayerInterface {
    public:
        NegamaxPlayer();

        NegamaxPlayer(const std::string& name);

        ~NegamaxPlayer() override;

        Tile getMove(const Board& board, ViewInterface& view) override;

        double negamax(const Board& board, int depth) const;

        double evaluate(const Board& board) const;
    };

}
