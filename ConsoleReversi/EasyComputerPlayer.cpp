#include <vector>
#include "EasyComputerPlayer.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer() : PlayerInterface("CPU") {}


    EasyComputerPlayer::EasyComputerPlayer(const std::string& name) : PlayerInterface(name) {}


    EasyComputerPlayer::~EasyComputerPlayer() = default;


    std::string EasyComputerPlayer::promptInput(Engine& engine, ViewInterface& view, bool isGameOver) {
        if (isGameOver) {
            return view.promptInput(engine, isGameOver);
        }

        view.displayStatus(engine, Status::FINDING_MOVE);

        return getMove(engine);
    }


    std::string EasyComputerPlayer::getMove(Engine& engine) {
        Board& board = engine.board;
        std::vector<Tile> validMoves;

        // find list of valid moves
        for (coordinate j = 0; j < 8; j++) {
            for (coordinate i = 0; i < 8; i++) {
                // position is empty and a valid move
                Tile move(i, j);
                if (board.isLegal(move)) {
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
}
