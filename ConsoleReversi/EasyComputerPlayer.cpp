#include <vector>
#include "EasyComputerPlayer.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer() = default;


    EasyComputerPlayer::~EasyComputerPlayer() = default;


    std::string EasyComputerPlayer::promptInput(Engine& engine, ViewInterface& view, bool isGameOver) {
        if (isGameOver) {
            return view.promptInput(engine, isGameOver);
        }

        view.displayStatus(engine, Status::FINDING_MOVE);

        return getMove(engine);
    }


    std::string EasyComputerPlayer::getMove(Engine& engine) {
        std::vector<int> validMovesX, validMovesY;
        int i, j, index;

        // find list of valid moves
        for (j = 0; j < 8; j++) {
            for (i = 0; i < 8; i++) {
                // position is empty and a valid move
                if (engine.isOpen(i, j) && engine.isValidMove(i, j, true)) {
                    validMovesX.push_back(i);
                    validMovesY.push_back(j);
                }
            }
        }

        // chose a valid move at random
        if (!validMovesX.empty()) {
            index = rand() % validMovesX.size();
            return engine.positionCoordsToString(validMovesX[index], validMovesY[index]);
        }

        return " ";
    }

    std::string EasyComputerPlayer::generateName() {
        return "CPU   ";
    }
}
