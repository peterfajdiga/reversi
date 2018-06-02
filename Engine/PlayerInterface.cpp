#include <iostream>
#include "PlayerInterface.h"

namespace reversi {
    PlayerInterface::PlayerInterface(color playerColor) : playerColor(playerColor), name("Player") {};


    PlayerInterface::PlayerInterface(color playerColor, const std::string& name) : playerColor(playerColor), name(name) {}


    PlayerInterface::~PlayerInterface() = default;

}
