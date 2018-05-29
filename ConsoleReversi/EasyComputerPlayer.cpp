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
        std::vector<Tile> validMoves;

        // find list of valid moves
        for (coordinate j = 0; j < 8; j++) {
            for (coordinate i = 0; i < 8; i++) {
                // position is empty and a valid move
                Tile move(i, j);
                if (engine.isOpen(move) && engine.isValidMove(move, true)) {
                    validMoves.emplace_back(move);
                }
            }
        }

        // chose a valid move at random
        if (!validMoves.empty()) {
            const size_t index = rand() % validMoves.size();
            return validMoves[index].toString();
        }

        return " ";
    }

    std::string EasyComputerPlayer::generateName() {
        return "CPU";
    }
}
