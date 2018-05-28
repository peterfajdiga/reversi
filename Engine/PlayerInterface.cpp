#include "PlayerInterface.h"


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
        mName = name;
        mName += ' ';
        switch (mId) {
            case 1: mName += "○"; break;
            case 2: mName += "●"; break;
            default: mName += std::to_string(mId);
        }
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
