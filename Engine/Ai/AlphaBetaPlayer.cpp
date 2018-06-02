#include <cmath>
#include <cassert>
#include "AlphaBetaPlayer.h"
#include "../helpers.h"


namespace reversi {

    AlphaBetaPlayer::AlphaBetaPlayer(color playerColor) : AiEvaluationPlayer(playerColor, "Alphabet") {};

    AlphaBetaPlayer::AlphaBetaPlayer(color playerColor, const std::string& name) : AiEvaluationPlayer(playerColor, name) {}

    AlphaBetaPlayer::~AlphaBetaPlayer() = default;


    const double PIECES_GAUSS_A1 =   1.066;
    const double PIECES_GAUSS_B1 =   18.29;
    const double PIECES_GAUSS_C1 =   25.82;
    const double PIECES_GAUSS_A2 = -0.5588;
    const double PIECES_GAUSS_B2 =   6.164;
    const double PIECES_GAUSS_C2 =    9.95;
    double AlphaBetaPlayer::estimateTimeByPieces(const size_t n_pieces) {
        // gauss function learned with depth 4
        const double exp1 = (n_pieces-PIECES_GAUSS_B1)/PIECES_GAUSS_C1;
        const double exp2 = (n_pieces-PIECES_GAUSS_B2)/PIECES_GAUSS_C2;
        return PIECES_GAUSS_A1 * exp(-exp1 * exp1) +
               PIECES_GAUSS_A2 * exp(-exp2 * exp2);
    }


    const double MOVES_QUAD_P2 =  0.001804020295611;
    const double MOVES_QUAD_P1 =  0.024237733457924;
    const double MOVES_QUAD_P0 = -0.020781778020523;
    double AlphaBetaPlayer::estimateTimeByMoves(const size_t n_moves) {
        // quadratic function learned with depth 4
        // 18 moves gives 1
        return n_moves * n_moves * MOVES_QUAD_P2 + n_moves * MOVES_QUAD_P1 * MOVES_QUAD_P0;
    }


    const size_t DEPTH_MIN = 4;
    const size_t DEPTH_MAX = 10;
    const size_t DEPTH_D = DEPTH_MAX-DEPTH_MIN;
    size_t AlphaBetaPlayer::estimateDepth(const size_t n_pieces, const size_t n_moves) {
        const double time = (estimateTimeByPieces(n_pieces) + estimateTimeByMoves(n_moves)) / 2.0;
        return (size_t)floor(DEPTH_MAX - time * DEPTH_D);
    }


    const double weights[8][8] = {
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 0.530, -0.225,  0.015, -0.010, -0.010,  0.015, -0.225,  0.530},
            { 1.160, -0.060,  0.510,  0.015,  0.015,  0.510, -0.060,  1.160},
            {-3.575, -1.810, -0.060, -0.225, -0.225, -0.060, -1.810, -3.575},
            {16.160, -3.575,  1.160,  0.530,  0.530,  1.160, -3.575, 16.160}
    };


    double AlphaBetaPlayer::evaluateStart(const Board& board) {
        if(board.getPiecesCount() >= 50){return negamax(board, 14, -INFINITY, INFINITY);}
        return negamax(board, 5, -INFINITY, INFINITY);
    }


    double AlphaBetaPlayer::negamax(const Board& board, size_t depth, double alpha, double beta) const {
        if (depth == 0 || board.isGameOver()) {
            return evaluate(board);
        }

        if (board.getCurrentPlayer() == playerColor) {
            // my turn
            double maxEvalScore = -INFINITY;

            for (const Tile& move : board.getLegalMoves()) {
                Board child(board, move);
                const double evalScore = negamax(child, depth - 1, alpha, beta);
                maxEvalScore = std::max(maxEvalScore, evalScore);
                alpha = std::max(alpha, maxEvalScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return maxEvalScore;

        } else {
            // opponent's turn
            double minEvalScore = INFINITY;

            for (const Tile& move : board.getLegalMoves()) {
                Board child(board, move);
                const double evalScore = negamax(child, depth - 1, alpha, beta);
                minEvalScore = std::min(minEvalScore, evalScore);
                beta = std::min(beta, minEvalScore);
                if (beta <= alpha) {
                    break;
                }
            }
            return minEvalScore;
        }
    }


    double AlphaBetaPlayer::evaluate(const Board& board) const {
        if (board.isGameOver()) {
            const gamestate state = board.getGamestate();
            if (state == draw) {
                return 0.0;
            } else {
                return INFINITY * state * playerColor;
            }
        }

        double weightsModified[8][8];
        std::copy(&weights[0][0], &weights[0][0]+8*8,&weightsModified[0][0]);


        if(board(0,0)== board.getCurrentPlayer()){
            weightsModified[0][1] *= -1;
            weightsModified[1][0] *= -1;
            weightsModified[1][1] *= -1;
        }
        if(board(7,7)== board.getCurrentPlayer()){
            weightsModified[7][6] *= -1;
            weightsModified[6][7] *= -1;
            weightsModified[6][6] *= -1;
        }
        if(board(0,7)== board.getCurrentPlayer()){
            weightsModified[0][6] *= -1;
            weightsModified[1][7] *= -1;
            weightsModified[1][6] *= -1;
        }
        if(board(7,0)== board.getCurrentPlayer()){
            weightsModified[7][1] *= -1;
            weightsModified[6][0] *= -1;
            weightsModified[6][1] *= -1;
        }
        double boardValue = 0.0;
        for (coordinate y = 0; y < 8; ++y) {
            for (coordinate x = 0; x < 8; ++x) {
                boardValue += 4.8 * (board(x, y) * weightsModified[x][y]);
            }
        }

        const double legalMovesValue =  board.getLegalMoves().size() * board.getCurrentPlayer(); // * getId();
        //if(board.getPiecesCount() >= 40) return (boardValue + legalMovesValue) * playerColor;
        return (boardValue) * playerColor;
    }
}
