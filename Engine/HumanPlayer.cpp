#include "HumanPlayer.h"


namespace reversi {

    HumanPlayer::HumanPlayer() = default;


    HumanPlayer::HumanPlayer(const std::string& name) : PlayerInterface(name) {}


    HumanPlayer::~HumanPlayer() = default;


    Tile HumanPlayer::getMove(const Board& board, ViewInterface& view) {
        return view.getMoveInput();
    }

}
