#include <iostream>
#include "PlayerInterface.h"
#include "Engine.h"


namespace reversi {
    PlayerInterface::PlayerInterface() : name("Player") {};


    PlayerInterface::PlayerInterface(const std::string& name) : name(name) {}


    PlayerInterface::~PlayerInterface() = default;


    int PlayerInterface::getId() const {
        return mId;
    }


    void PlayerInterface::setScore(int score) {
        mScore = score;
    }


    int PlayerInterface::getScore() const {
        return mScore;
    }

}
