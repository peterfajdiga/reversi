#include <vector>
#include "EasyComputerPlayer.h"


namespace reversi {
    EasyComputerPlayer::EasyComputerPlayer() : PlayerInterface("CPU") {}


    EasyComputerPlayer::EasyComputerPlayer(const std::string& name) : PlayerInterface(name) {}


    EasyComputerPlayer::~EasyComputerPlayer() = default;


    std::string EasyComputerPlayer::promptInput(Engine& engine, ViewInterface& view, bool isGameOver) {
        if (isGameOver) {
            return view.promptInput(isGameOver);
        }

        view.displayStatus(Status::FINDING_MOVE);

        return getMove(engine);
    }


    std::string EasyComputerPlayer::getMove(Engine& engine) {
        const Board& board = engine.getBoard();

        // find list of valid moves
        std::vector<Tile> validMoves = board.getLegalMoves();

        // chose a valid move at random
        if (!validMoves.empty()) {
            const size_t index = rand() % validMoves.size();
            return validMoves[index].toString();
        }

        return " ";
    }
}
