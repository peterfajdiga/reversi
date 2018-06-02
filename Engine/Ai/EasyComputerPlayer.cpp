#include "EasyComputerPlayer.h"
#include "../helpers.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer() : AiPlayerTimed("CPU") {}

    EasyComputerPlayer::EasyComputerPlayer(const std::string& name) : AiPlayerTimed(name) {}

    EasyComputerPlayer::~EasyComputerPlayer() = default;

    Tile EasyComputerPlayer::getMoveTimed(const Board& board) {
        return helpers::getRandom(board.getLegalMoves());
    }
}
