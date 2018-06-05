#include "HumanPlayer.h"


namespace reversi {

    HumanPlayer::HumanPlayer(color playerColor) : PlayerInterface(playerColor) {}

    HumanPlayer::HumanPlayer(color playerColor, const std::string& name) : PlayerInterface(playerColor, name) {}

    HumanPlayer::~HumanPlayer() = default;


    Tile HumanPlayer::getMove(const Board& board, const std::vector<Tile>& moveHistory, ViewInterface& view) {
        return view.getMoveInput();
    }

}
