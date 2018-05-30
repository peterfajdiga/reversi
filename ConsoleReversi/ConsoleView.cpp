#include <iostream>
#include "ConsoleView.h"
#include "EasyComputerPlayer.h"


namespace reversi {

#ifdef _WIN32
    const char* const WHITE = "o";
    const char* const BLACK = "x";
#else
    const char* const WHITE = "○";
    const char* const BLACK = "●";
#endif


    ConsoleView::ConsoleView() = default;


    ConsoleView::~ConsoleView() = default;


    void ConsoleView::setupGame(const Engine& engine) {
        using namespace std;

        cout << "\n\nConsole Reversi by jsmreese.\n\n";
        cout << "At any time, enter:\n- 'n' for a new game\n- 'q' to quit playing\n- 'c' to switch the current player to a computer player\n\n";
        cout << "To make a move, enter the column letter followed by\n";
        cout << "the row number of the desired position, e.g. 'f4'.\n\n";
        cout << "Columns are from 'a' to 'h', and rows are from '1' to '8'." << endl;
    }


    void ConsoleView::teardownGame(const Engine& engine) {

    }


    void ConsoleView::displayState(const Engine& engine, bool isGameOver) {
        using namespace std;

        const score s1 = engine.getPlayer(1)->getScore();
        const score s2 = engine.getPlayer(2)->getScore();

        if (isGameOver) {
            cout << "\n\n-----------------------------";
            cout << "\n\n" + drawBoard(engine.getBoard()) << endl;

            cout << "\n ** Game Over **\n\n";
            cout << "\n\n" + drawScore(engine);

            if (s1 == s2) {
                cout << "Game is a draw!" << endl;
            }
            else {
                cout << "\n Congratulations, ";
                cout << getFormattedName(*engine.getPlayer(s1 > s2 ? 1 : 2)) + "!" << endl;
            }

        } else {
            cout << "\n\n-----------------------------";

            cout << "\n\n" + drawScore(engine);

            cout << "\n\n" + drawBoard(engine.getBoard()) + "\n";
        }
    }


    std::string ConsoleView::promptInput(Engine& engine, bool isGameOver) {
        using namespace std;

        string input;

        if (isGameOver) {
            cout << "\n\nEnter 'n' to play again, or 'q' to quit playing: ";

            cin >> input;

            return input;
        }

        cout << "\n" + getFormattedName(*engine.getPlayer()) + ", enter a move: ";
        cin >> input;

        if (input.length() == 1 && tolower(input[0]) == 99) {
            // 'c' - switch to computer player

            EasyComputerPlayer* player = new EasyComputerPlayer;

            engine.setPlayer(player);

            return engine.getPlayer()->promptInput(engine, *this);
        }

        return input;
    }


    void ConsoleView::displayStatus(const Engine& engine, const Status status, const std::string& input) {
        using namespace std;

        switch (status) {
        case Status::CANNOT_MOVE:
            cout << "\n\n ** " + getFormattedName(*engine.getPlayer()) + " is unable to move. **" << endl;
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
            cout << "\n\n" + getFormattedName(*engine.getPlayer()) + " moved at position " + input + "." << endl;
            break;

        case Status::FINDING_MOVE:
            cout << "\n\n" + getFormattedName(*engine.getPlayer()) + " searching for move..." << endl;
            break;
        }
    }


    std::string ConsoleView::drawBoard(const Board& board) const {
        using namespace std;

        string boardString = "   a b c d e f g h\n\n";

        for (Tile tile(0, 0); tile.y < 8; tile.y++) {
            boardString += to_string(tile.y + 1) + " ";
            for (tile.x = 0; tile.x < 8; tile.x++) {
                boardString += ' ';
                const int position = board[tile];
                switch (position) {
                    case 0: boardString += '.'; break;  // unoccupied
                    case 1: boardString += WHITE; break;
                    case 2: boardString += BLACK; break;
                    default: boardString += to_string(position);
                }
            }

            boardString += "  " + to_string(tile.y + 1) + "\n";
        }

        boardString += "\n   a b c d e f g h\n";

        return boardString;
    }


    std::string ConsoleView::drawScore(const Engine &engine) const {
        const std::string p1Name = getFormattedName(*engine.getPlayer(1));
        const std::string p2Name = getFormattedName(*engine.getPlayer(2));

        const std::string p1Score = std::to_string(engine.getPlayer(1)->getScore());
        const std::string p2Score = std::to_string(engine.getPlayer(2)->getScore());

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
        const id playerId = player.getId();
        switch (playerId) {
            case 1: name += WHITE; break;
            case 2: name += BLACK; break;
            default: name += std::to_string(playerId);
        }
        name += ' ';
        name += player.name;
        return name;
    }

}
