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
        static void reroot(MCTree*& root, size_t index);
        static void reroot(MCTree*& root, const Tile& move);
    };


    class MonteCarloTreePlayer : public MonteCarloPlayer {
    public:
        MonteCarloTreePlayer(color playerColor);

        MonteCarloTreePlayer(color playerColor, const std::string& name);

        ~MonteCarloTreePlayer() override;

        Tile getMoveTimed(const Board& board, const std::vector<Tile>& moveHistory) override;

    private:
        MCTree* root;
        size_t lastPiecesCount;
        size_t lastMoveHistoryLength;
    };

}
