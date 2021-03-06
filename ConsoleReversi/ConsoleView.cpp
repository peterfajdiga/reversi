#include <iostream>
#include <cassert>
#include "ConsoleView.h"
#include "../Engine/Ai/EasyComputerPlayer.h"
#include "../Engine/Ai/MonteCarloPlayer.h"
#include "../Engine/helpers.h"
#include "../Engine/Ai/AlphaBetaPlayer.h"
#include "../Engine/Ai/AiHeuristicPlayer.h"
#include "../Engine/Ai/MonteCarloTreePlayer.h"


#ifdef _WIN32
#define UNOCCUPIED "."
#define UNOCCUPIED_LEGAL ","
#define WHITE "o"
#define BLACK "x"
#else
#define UNOCCUPIED "·"
#define UNOCCUPIED_LEGAL "•"
#define WHITE "○"
#define BLACK "●"
#endif


namespace reversi {


    ConsoleView::ConsoleView() = default;


    ConsoleView::~ConsoleView() = default;


    void ConsoleView::setupGame() {
        using namespace std;

        cout << "\n\nConsole Reversi originally by jsmreese.\n\n";
        cout << "At any time, enter:\n- 'n' for a new game\n- 'q' to quit playing\n- 'h' to highlight available moves\n- 'c' to switch the current player to a computer player\n\n";
        cout << "To make a move, enter the column letter followed by\n";
        cout << "the row number of the desired position, e.g. 'f4'.\n\n";
        cout << "Columns are from 'a' to 'h', and rows are from '1' to '8'." << endl;
    }


    void ConsoleView::teardownGame() {

    }


    void ConsoleView::displayState(bool isGameOver) {
        using namespace std;

        const score s1 = engine->getBoard().getScoreWhite();
        const score s2 = engine->getBoard().getScoreBlack();

        if (isGameOver) {
            cout << "\n\n-----------------------------";
            cout << "\n\n" << drawBoard(engine->getBoard(), false) << endl;

            cout << "\n ** Game Over **\n\n";
            cout << "\n\n" << drawScore();

            if (s1 == s2) {
                cout << "Game is a draw!" << endl;
            }
            else {
                cout << "\n Congratulations, ";
                cout << getFormattedName(*engine->getPlayer(s1 > s2 ? white : black)) << "!" << endl;
            }

        } else {
            cout << "\n\n-----------------------------";

            cout << "\n\n" << drawScore();

            cout << "\n\n" << drawBoard(engine->getBoard(), false) << "\n";
        }
    }


    Tile ConsoleView::getMoveInput() {
        const Board& board = engine->getBoard();

        ask:
        std::cout << "\n" << getFormattedName(*engine->getPlayer()) << ", enter a move: ";
        std::string input;
        std::cin >> input;

        switch (input.length()) {
            case 1:
                switch (input[0]) {
                    case 'q': engine->quitGame(); break;
                    case 'n': engine->newGame(); break;
                    case 'h': std::cout << "\nLegal moves are now marked with " << UNOCCUPIED_LEGAL << "\n\n\n" << drawBoard(board, true) << "\n"; goto ask;
                    case 'c': selectAi(); break;
                    default: goto ask;
                } break;
            case 2: return Tile(input);
            default: goto ask;
        }

        throw NoMoveException();
    }


    void ConsoleView::onGameOver() {
        ask:
        std::string input;
        do {
            std::cout << "\n\nEnter 'n' to play again, or 'q' to quit playing: ";
            std::cin >> input;
        } while (input.length() != 1);

        switch (input[0]) {
            case 'q': engine->quitGame(); break;
            case 'n': engine->newGame(); break;
            default: goto ask;
        }
    }


    void ConsoleView::selectAi() const {
        std::cout << "Select an opponent:\n"
                  << " - EasyComputerPlayer   (c)\n"
                  << " - HeuristicPlayer      (h)\n"
                  << " - MonteCarloPlayer     (m)\n"
                  << " - MonteCarloTreePlayer (t)\n"
                  << " - AlphaBetaPlayer      (a)\n";
        ask:
        std::cout << "Your choice: ";
        std::string input;
        std::cin >> input;

        if (input.length() != 1) {
            goto ask;
        }
        switch (input[0]) {
            case 'c': engine->playerToAi<EasyComputerPlayer>(); break;
            case 'h': engine->playerToAi<AiHeuristicPlayer>(); break;
            case 'm': engine->playerToAi<MonteCarloPlayer>(); break;
            case 't': engine->playerToAi<MonteCarloTreePlayer>(); break;
            case 'a': engine->playerToAi<AlphaBetaPlayer>(); break;
            default: goto ask;
        }
    }


    void ConsoleView::displayStatus(Status status) {
        using namespace std;

        switch (status) {
        case Status::CANNOT_MOVE:
            cout << "\n\n ** " << getFormattedName(*engine->getPlayer(engine->getBoard().getCurrentPlayer())) << " is unable to move. **" << endl;
            break;

        case Status::INVALID_MOVE:
            cout << "\n\n ** Invalid move. Move must flip at least one of the opponent's pieces. **" << endl;
            break;

        case Status::OUT_OF_BOUNDS:
            cout << "\n\n ** Invalid move. Position is not on the board. **" << endl;
            break;

        case Status::POSITION_FILLED:
            cout << "\n\n ** Invalid move. Position is already filled. **" << endl;
            break;

        case Status::SUCCESS:
            cout << "\n\n" << getFormattedName(*engine->getLastMovePlayer()) << " moved at position " << engine->getLastMoveTile() << "." << endl;
            break;

        case Status::FINDING_MOVE:
            cout << "\n\n" << getFormattedName(*engine->getPlayer()) << " searching for move..." << endl;
            break;
        }
    }


    std::string ConsoleView::drawBoard(const Board& board, bool highlight) const {
        std::string boardString = "   a b c d e f g h\n";

        const std::vector<Tile>& legalMoves = board.getLegalMoves();

        for (Tile tile(0, 0); tile.y < 8; tile.y++) {
            boardString += std::to_string(tile.y + 1) + " ";
            for (tile.x = 0; tile.x < 8; tile.x++) {
                boardString += ' ';
                const color position = board[tile];
                switch (position) {
                    case unoccupied: boardString += highlight && helpers::contains(legalMoves, tile) ? UNOCCUPIED_LEGAL : UNOCCUPIED; break;
                    case white: boardString += WHITE; break;
                    case black: boardString += BLACK; break;
                    default: boardString += std::to_string(position);
                }
            }

            boardString += "  " + std::to_string(tile.y + 1) + "\n";
        }

        boardString += "   a b c d e f g h\n";

        return boardString;
    }


    std::string ConsoleView::drawScore() const {
        const std::string p1Name = getFormattedName(*engine->getPlayer(white));
        const std::string p2Name = getFormattedName(*engine->getPlayer(black));

        const std::string p1Score = std::to_string(engine->getBoard().getScoreWhite());
        const std::string p2Score = std::to_string(engine->getBoard().getScoreBlack());

        const size_t maxLength = std::max(p1Name.size(), p2Name.size()) + std::max(p1Score.size(), p2Score.size());
        const size_t p1Padding = maxLength - p1Name.size() - p1Score.size();
        const size_t p2Padding = maxLength - p2Name.size() - p2Score.size();

        std::string score = "Score\n";

        score += p1Name + ": ";
        for (int i = 0; i < p1Padding; ++i) {
            score += ' ';
        }
        score += p1Score + "\n";

        score += p2Name + ": ";
        for (int i = 0; i < p2Padding; ++i) {
            score += ' ';
        }
        score += p2Score + "\n";

        return score;
    }


    std::string ConsoleView::getFormattedName(const PlayerInterface& player) const {
        std::string name;
        const color playerId = player.playerColor;
        switch (playerId) {
            case white: name += WHITE; break;
            case black: name += BLACK; break;
            default: assert(false);
        }
        name += ' ';
        name += player.name;
        return name;
    }

}
