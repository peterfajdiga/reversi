#include "HumanPlayer.h"


namespace reversi {

    HumanPlayer::HumanPlayer(color playerColor) : PlayerInterface(playerColor) {}

    HumanPlayer::HumanPlayer(color playerColor, const std::string& name) : PlayerInterface(playerColor, name) {}

    HumanPlayer::~HumanPlayer() = default;


    Tile HumanPlayer::getMove(const Board& board, ViewInterface& view) {
        return view.getMoveInput();
    }

}
