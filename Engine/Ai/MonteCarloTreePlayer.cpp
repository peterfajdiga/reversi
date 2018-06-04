#include <cassert>
#include <cmath>
#include "MonteCarloTreePlayer.h"
#include "../helpers.h"


namespace reversi {

    const double C = sqrt(2);
    const double EPS = 1e-14;

    class Tree {
    public:
        Tree* const parent;
        const Board board;
        size_t wins, runs;
        std::vector<Tree> children;

        Tree(const Board& board) : parent(nullptr), board(board), wins(0), runs(0) {}
        Tree(Tree& parent, const Tile& move) : parent(&parent), board(parent.board, move), wins(0), runs(0) {}

        void expand() {
            assert(children.empty());
            for (const Tile& move : board.getLegalMoves()) {
                children.emplace_back(Tree(*this, move));
            }
        }

        double selectionFitness() const {
            // UCT
            return (double)wins / (runs+EPS) + C * sqrt(log(parent->runs+1) / (runs+EPS)) + rand() * EPS;
        }

        Tree& select() {
            Tree* bestTree = this;
            while (!bestTree->children.empty()) {
                double maxFitness = -INFINITY;
                for (Tree& tree : bestTree->children) {
                    const double fitness = tree.selectionFitness();
                    if (fitness > maxFitness) {
                        maxFitness = fitness;
                        bestTree = &tree;
                    }
                }
            }
            return *bestTree;
        }

        void propagate(const gamestate winner) {
            Tree* tree = this;
            while (tree->parent != nullptr) {
                if (winner / 2 == tree->parent->board.getCurrentPlayer()) {
                    tree->wins++;
                }
                tree->runs++;
                tree = tree->parent;
            }
        }
    };

    MonteCarloTreePlayer::MonteCarloTreePlayer(color playerColor) : MonteCarloPlayer(playerColor, "MTree") {}

    MonteCarloTreePlayer::MonteCarloTreePlayer(color playerColor, const std::string& name) : MonteCarloPlayer(playerColor, name) {}

    MonteCarloTreePlayer::~MonteCarloTreePlayer() = default;

    const clock_t SAMPLE_TIME = (clock_t)(1 * CLOCKS_PER_SEC);
    Tile MonteCarloTreePlayer::getMoveTimed(const Board& board) {
        Tree root(board);

        // sample
        const clock_t startTime = clock();
        while (clock() - startTime < SAMPLE_TIME) {
            Tree& nodeToExpand = root.select();
            if (nodeToExpand.board.isGameOver()) {
                nodeToExpand.propagate(nodeToExpand.board.getGamestate());
            } else {
                nodeToExpand.expand();
                Tree& nodeToSimulate = helpers::getRandom(nodeToExpand.children);
                const gamestate winner = playRandom(nodeToSimulate.board);
                nodeToSimulate.propagate(winner);
            }
        }

        // return most sampled
        const std::vector<Tile>& legalMoves = board.getLegalMoves();
        const size_t n = legalMoves.size();
        size_t mostRuns = 0;
        Tile bestMove = legalMoves[0];  // default move
        for (size_t i = 0; i < n; ++i) {
            const size_t runs = root.children[i].runs;
            if (runs > mostRuns) {
                mostRuns = runs;
                bestMove = legalMoves[i];
            }
        }
        return bestMove;
    }
}
