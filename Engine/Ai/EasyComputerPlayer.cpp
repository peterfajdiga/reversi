#include "EasyComputerPlayer.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer() : AiPlayerTimed("CPU") {}

    EasyComputerPlayer::EasyComputerPlayer(const std::string& name) : AiPlayerTimed(name) {}

    EasyComputerPlayer::~EasyComputerPlayer() = default;

    Tile EasyComputerPlayer::getMoveTimed(const Board& board) {
        std::vector<Tile> legalMoves = board.getLegalMoves();
        const size_t index = rand() % legalMoves.size();
        return legalMoves[index];
    }
}
