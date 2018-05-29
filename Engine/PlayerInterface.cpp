#include "PlayerInterface.h"
#include "Engine.h"


namespace reversi {
    PlayerInterface::PlayerInterface() = default;


    PlayerInterface::~PlayerInterface() = default;


    void PlayerInterface::setId(int id) {
        mId = id;
        setName(generateName());
    }


    int PlayerInterface::getId() const {
        return mId;
    }


    void PlayerInterface::setName(const std::string& name) {
        switch (mId) {
            case 1: mName = white; break;
            case 2: mName = black; break;
            default: mName += std::to_string(mId);
        }
        mName += ' ';
        mName += name;
    }


    std::string PlayerInterface::getName() const {
        return mName;
    }



    void PlayerInterface::setScore(int score) {
        mScore = score;
    }


    int PlayerInterface::getScore() const {
        return mScore;
    }

    std::string PlayerInterface::generateName() {
        return "Player";
    }

}
