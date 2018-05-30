#include "HumanPlayer.h"


namespace reversi {

    HumanPlayer::HumanPlayer() = default;


    HumanPlayer::HumanPlayer(const std::string& name) : PlayerInterface(name) {}


    HumanPlayer::~HumanPlayer() = default;


    std::string HumanPlayer::promptInput(Engine& engine, ViewInterface& view, bool isGameOver) {
        return view.promptInput(engine, isGameOver);
    }

}
