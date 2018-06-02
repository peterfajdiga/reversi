#include "EasyComputerPlayer.h"
#include "../helpers.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer(color playerColor) : AiPlayerTimed(playerColor, "CPU") {}

    EasyComputerPlayer::EasyComputerPlayer(color playerColor, const std::string& name) : AiPlayerTimed(playerColor, name) {}

    EasyComputerPlayer::~EasyComputerPlayer() = default;

    Tile EasyComputerPlayer::getMoveTimed(const Board& board) {
        return board.getLegalMoves()[0];
    }
}
