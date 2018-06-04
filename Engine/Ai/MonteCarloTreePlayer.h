#pragma once

#include "MonteCarloPlayer.h"


namespace reversi {

    class MCTree {
    public:
        MCTree* parent;
        const Board board;
        size_t wins, runs;
        std::vector<MCTree*> children;

        MCTree(const Board& board);
        MCTree(MCTree& parent, const Tile& move);

        void expand();
        double selectionFitness() const;
        MCTree& select();
        void propagate(const gamestate winner);
        void clear();
        std::vector<size_t> findState(const Board& state);
        static void reroot(MCTree*& root, size_t index);

    private:
        bool findState(std::vector<size_t>& moves, const Board& state, size_t depth);
    };


    class MonteCarloTreePlayer : public MonteCarloPlayer {
    public:
        MonteCarloTreePlayer(color playerColor);

        MonteCarloTreePlayer(color playerColor, const std::string& name);

        ~MonteCarloTreePlayer() override;

        Tile getMoveTimed(const Board& board) override;

    private:
        MCTree* root;
        size_t lastPiecesCount;
    };

}
