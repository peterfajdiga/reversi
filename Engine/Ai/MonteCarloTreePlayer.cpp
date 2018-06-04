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
        const size_t n = root->board.getLegalMoves().size();
        for (size_t i = 0; i < n; ++i) {
            if (i != index) {
                root->children[i]->clear();
            }
        }
        MCTree* newRoot = root->children[index];
        newRoot->parent = nullptr;
        delete root;
        root = newRoot;
    }

    bool MCTree::findState(std::vector<size_t>& moves, const Board& state, const size_t depth) {
        if (depth == 0) {
            return board == state;
        }
        const size_t n = board.getLegalMoves().size();
        for (size_t i = 0; i < n; ++i) {
            if (children[i]->findState(moves, state, depth-1)) {
                moves.insert(moves.begin(), i);
                return true;
            }
        }
        return false;
    }

    std::vector<size_t> MCTree::findState(const Board& state) {
        std::vector<size_t> moves;
        findState(moves, state, state.getPiecesCount() - board.getPiecesCount());
        return moves;
    }


    MonteCarloTreePlayer::MonteCarloTreePlayer(color playerColor) : MonteCarloPlayer(playerColor, "MTree"), root(nullptr) {}

    MonteCarloTreePlayer::MonteCarloTreePlayer(color playerColor, const std::string& name) : MonteCarloPlayer(playerColor, name), root(nullptr) {}

    MonteCarloTreePlayer::~MonteCarloTreePlayer() {
        root->clear();
        delete root;
    }

    const clock_t SAMPLE_TIME = (clock_t)(1 * CLOCKS_PER_SEC);
    Tile MonteCarloTreePlayer::getMoveTimed(const Board& board) {
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
            for (const size_t move : root->findState(board)) {
                MCTree::reroot(root, move);
            }
            assert(root->board == board);
        }

        // sample
        const clock_t startTime = clock();
        while (clock() - startTime < SAMPLE_TIME) {
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
