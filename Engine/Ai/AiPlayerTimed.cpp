#include <iostream>
#include "AiPlayerTimed.h"


namespace reversi {

    AiPlayerTimed::AiPlayerTimed(color playerColor) : PlayerInterface(playerColor, "CPU") {}

    AiPlayerTimed::AiPlayerTimed(color playerColor, const std::string& name) : PlayerInterface(playerColor, name) {}

    AiPlayerTimed::~AiPlayerTimed() = default;

    Tile AiPlayerTimed::getMove(const Board& board, ViewInterface& view) {
        view.displayStatus(Status::FINDING_MOVE);
        const clock_t startTime = clock();
        Tile move = getMoveTimed(board);
        //fprintf(stderr, "%ld\t%ld\t%lf\n", board.getPiecesCount(), board.getLegalMoves().size(), (double)(clock() - startTime) / CLOCKS_PER_SEC);
        //printf("PiecesCount: %ld | LegalMovesCount: %ld\n", board.getPiecesCount(), board.getLegalMoves().size());
        std::cout << "Finding move took " << (double)(clock() - startTime) / CLOCKS_PER_SEC << " seconds\n";
        return move;
    }
}
