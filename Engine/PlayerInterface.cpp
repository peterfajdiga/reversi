#include <iostream>
#include "PlayerInterface.h"

namespace reversi {
    PlayerInterface::PlayerInterface() : name("Player") {};


    PlayerInterface::PlayerInterface(const std::string& name) : name(name) {}


    PlayerInterface::~PlayerInterface() = default;


    color PlayerInterface::getId() const {
        return mId;
    }


    void PlayerInterface::setScore(const score s) {
        mScore = s;
    }


    score PlayerInterface::getScore() const {
        return mScore;
    }

}
