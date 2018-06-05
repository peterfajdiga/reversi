#include <cassert>
#include <cmath>
#include "MonteCarloTreePlayer.h"
#include "../helpers.h"


namespace reversi {

    MCTree::MCTree(const Board& board) : parent(nullptr), board(board), wins(0), runs(0) {}
    MCTree::MCTree(MCTree& parent, const Tile& move) : parent(&parent), board(parent.board, move), wins(0), runs(0) {}

    void MCTree::expand() {
        assert(children.empty());
        for (const Tile& move : board.getLegalMoves()) {
            children.emplace_back(new MCTree(*this, move));
        }
    }

    const double C = 1.414213562373095;  // sqrt(2)
    const double EPS = 1e-14;
    double MCTree::selectionFitness() const {
        // UCT
        return (double)wins / (runs+EPS) + C * sqrt(log(parent->runs+1) / (runs+EPS)) + rand() * EPS;
    }

    MCTree& MCTree::select() {
        MCTree* bestTree = this;
        while (!bestTree->children.empty()) {
            double maxFitness = -INFINITY;
            for (MCTree* tree : bestTree->children) {
                const double fitness = tree->selectionFitness();
                if (fitness > maxFitness) {
                    maxFitness = fitness;
                    bestTree = tree;
                }
            }
        }
        return *bestTree;
    }

    void MCTree::propagate(const gamestate winner) {
        MCTree* tree = this;
        while (tree->parent != nullptr) {
            if (winner / 2 == tree->parent->board.getCurrentPlayer()) {
                tree->wins++;
            }
            tree->runs++;
            tree = tree->parent;
        }
    }

    void MCTree::clear() {
        for (MCTree* tree : children) {
            tree->clear();
            delete tree;
        }
    }

    void MCTree::reroot(MCTree*& root, size_t index) {
        MCTree* newRoot;
        if (root->children.empty()) {
            // not expanded, create correct child
            newRoot = new MCTree(Board(root->board, root->board.getLegalMoves()[index]));
            root->clear();

        } else {
            // expanded, select new root from children
            const size_t n = root->board.getLegalMoves().size();
            for (size_t i = 0; i < n; ++i) {
                if (i != index) {
                    root->children[i]->clear();
                }
            }
            newRoot = root->children[index];
            newRoot->parent = nullptr;
        }
        delete root;
        root = newRoot;
    }

    void MCTree::reroot(MCTree*& root, const Tile& move) {
        const std::vector<Tile>& legalMoves = root->board.getLegalMoves();
        const size_t n = legalMoves.size();
        for (size_t i = 0; i < n; ++i) {
            if (legalMoves[i] == move) {
                reroot(root, i);
                return;
            }
        }
    }


    MonteCarloTreePlayer::MonteCarloTreePlayer(color playerColor) : MonteCarloPlayer(playerColor, "MTree"), root(nullptr) {}

    MonteCarloTreePlayer::MonteCarloTreePlayer(color playerColor, const std::string& name) : MonteCarloPlayer(playerColor, name), root(nullptr) {}

    MonteCarloTreePlayer::~MonteCarloTreePlayer() {
        root->clear();
        delete root;
    }

    Tile MonteCarloTreePlayer::getMoveTimed(const Board& board, const std::vector<Tile>& moveHistory) {
        if (board.getPiecesCount() < lastPiecesCount) {
            // new game
            if (root != nullptr) {
                root->clear();
                delete root;
                root = nullptr;
            }
        }
        lastPiecesCount = board.getPiecesCount();

        if (root == nullptr) {
            // first move
            root = new MCTree(board);
        } else {
            const size_t newMoveHistoryLength = moveHistory.size();
            for (size_t i = lastMoveHistoryLength+1; i < newMoveHistoryLength; ++i) {
                MCTree::reroot(root, moveHistory[i]);
            }
            assert(root->board == board);
        }
        lastMoveHistoryLength = moveHistory.size();

        // sample
        const clock_t startTime = clock();
        while (clock() - startTime < MOVE_TIME) {
            MCTree& nodeToExpand = root->select();
            if (nodeToExpand.board.isGameOver()) {
                nodeToExpand.propagate(nodeToExpand.board.getGamestate());
            } else {
                nodeToExpand.expand();
                MCTree& nodeToSimulate = *helpers::getRandom(nodeToExpand.children);
                const gamestate winner = playRandom(nodeToSimulate.board);
                nodeToSimulate.propagate(winner);
            }
        }

        // choose most sampled
        const std::vector<Tile>& legalMoves = board.getLegalMoves();
        const size_t n = legalMoves.size();
        size_t mostRuns = 0;
        size_t bestMove = 0;  // default move
        for (size_t i = 0; i < n; ++i) {
            const size_t runs = root->children[i]->runs;
            if (runs > mostRuns) {
                mostRuns = runs;
                bestMove = i;
            }
        }

        // reroot according to our chosen move
        MCTree::reroot(root, bestMove);

        return legalMoves[bestMove];
    }
}
