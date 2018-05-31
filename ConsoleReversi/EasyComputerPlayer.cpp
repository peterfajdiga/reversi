#include <vector>
#include "EasyComputerPlayer.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer() : PlayerInterface("CPU") {}


    EasyComputerPlayer::EasyComputerPlayer(const std::string& name) : PlayerInterface(name) {}


    EasyComputerPlayer::~EasyComputerPlayer() = default;


    Tile EasyComputerPlayer::getMove(const Board& board, ViewInterface& view) {
        view.displayStatus(Status::FINDING_MOVE);

        std::vector<Tile> legalMoves = board.getLegalMoves();
        const size_t index = rand() % legalMoves.size();
        return legalMoves[index];
    }
}
