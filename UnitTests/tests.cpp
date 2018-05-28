#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "TestEngine.h"

reversi::TestEngine engine;

TEST_CASE("initBoard", "[initboard]") {
    int i, j;

    engine.initBoard();

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (i == 3 && j == 3 || i == 4 && j == 4) {
                REQUIRE(engine.getPosition(i, j) == 2);
            }
            else if (i == 3 && j == 4 || i == 4 && j == 3) {
                REQUIRE(engine.getPosition(i, j) == 1);
            }
            else {
                REQUIRE(engine.getPosition(i, j) == 0);
            }
        }
    }
}


TEST_CASE("isOnBoard", "[isonboard]") {
    int i, j;

    engine.initBoard();

    // test all board positions
    // and one index above and below the max/min indexes
    for (i = -1; i < 9; i++) {
        for (j = -1; j < 9; j++) {
            if (i >= 0 && i <= 7 && j >= 0 && j <= 7) {
                REQUIRE(engine.isOnBoard(i, j));
            }
            else {
                REQUIRE_FALSE(engine.isOnBoard(i, j));
            }
        }
    }
}


// requires starting with mCurrentPlayer == 1
TEST_CASE("togglePlayer", "[toggleplayer]") {
    REQUIRE(engine.getPlayer()->getId() == 1);

    engine.togglePlayer();
    REQUIRE(engine.getPlayer()->getId() == 2);

    engine.togglePlayer();
    REQUIRE(engine.getPlayer()->getId() == 1);
}


// requires starting with mCurrentPlayer == 1
TEST_CASE("canMove", "[canmove]") {
    engine.clearBoard();

    SECTION("can't move on an empty board") {
        REQUIRE_FALSE(engine.canMove());
    }

    SECTION("only player 1 can move") {
        engine.setPosition(0, 0, 1);
        engine.setPosition(1, 0, 2);
        REQUIRE(engine.canMove());

        engine.togglePlayer(); // player 2
        REQUIRE_FALSE(engine.canMove());

        engine.togglePlayer(); // player 1
        REQUIRE(engine.canMove());
    }

    SECTION("avoid buffer overrun when checking for valid moves") {
        engine.setPosition(0, 0, 1);
        engine.setPosition(1, 0, 1);
        engine.setPosition(2, 0, 1);
        engine.setPosition(3, 0, 1);
        engine.setPosition(4, 0, 1);
        engine.setPosition(5, 0, 1);
        engine.setPosition(6, 0, 1);
        engine.setPosition(7, 0, 1);
        engine.setPosition(0, 1, 1);
        engine.setPosition(1, 1, 2);
        REQUIRE(engine.canMove());

        engine.togglePlayer(); // player 2
        REQUIRE_FALSE(engine.canMove());

        engine.togglePlayer(); // player 1
        REQUIRE(engine.canMove());
    }
}


TEST_CASE("updateScores", "[updatescores]") {
    engine.clearBoard();

    SECTION("tie game") {
        engine.setPosition(0, 0, 1);
        engine.setPosition(1, 0, 2);
        engine.updateScores();
        REQUIRE(engine.getPlayer(1)->getScore() == 1);
        REQUIRE(engine.getPlayer(2)->getScore() == 1);

        engine.updateScores(true);
        REQUIRE(engine.getPlayer(1)->getScore() == 1);
        REQUIRE(engine.getPlayer(2)->getScore() == 1);
    }

    SECTION("player 1 wins") {
        engine.setPosition(0, 0, 1);
        engine.setPosition(0, 1, 1);
        engine.setPosition(1, 0, 2);
        engine.updateScores();
        REQUIRE(engine.getPlayer(1)->getScore() == 2);
        REQUIRE(engine.getPlayer(2)->getScore() == 1);

        engine.updateScores(true);
        REQUIRE(engine.getPlayer(1)->getScore() == 63);
        REQUIRE(engine.getPlayer(2)->getScore() == 1);
    }

    SECTION("player 2 wins") {
        engine.setPosition(0, 0, 2);
        engine.setPosition(0, 1, 2);
        engine.setPosition(1, 0, 1);
        engine.updateScores();
        REQUIRE(engine.getPlayer(1)->getScore() == 1);
        REQUIRE(engine.getPlayer(2)->getScore() == 2);

        engine.updateScores(true);
        REQUIRE(engine.getPlayer(1)->getScore() == 1);
        REQUIRE(engine.getPlayer(2)->getScore() == 63);
    }
}


TEST_CASE("updateState", "[updatestate]") {
    engine.initBoard();

    SECTION("out of bounds") {
        REQUIRE(engine.updateState("!!") == reversi::Status::OUT_OF_BOUNDS);
        REQUIRE(engine.updateState("a9") == reversi::Status::OUT_OF_BOUNDS);
        REQUIRE(engine.updateState("9a") == reversi::Status::OUT_OF_BOUNDS);
        REQUIRE(engine.updateState("1i") == reversi::Status::OUT_OF_BOUNDS);
    }

    SECTION("position filled") {
        REQUIRE(engine.updateState("d4") == reversi::Status::POSITION_FILLED);
        REQUIRE(engine.updateState("d5") == reversi::Status::POSITION_FILLED);
        REQUIRE(engine.updateState("e4") == reversi::Status::POSITION_FILLED);
        REQUIRE(engine.updateState("e5") == reversi::Status::POSITION_FILLED);
    }

    SECTION("invalid move") {
        REQUIRE(engine.updateState("f4") == reversi::Status::INVALID_MOVE);
        REQUIRE(engine.updateState("e3") == reversi::Status::INVALID_MOVE);
        REQUIRE(engine.updateState("a1") == reversi::Status::INVALID_MOVE);
        REQUIRE(engine.updateState("h8") == reversi::Status::INVALID_MOVE);
    }

    SECTION("valid move") {
        REQUIRE(engine.updateState("f5") == reversi::Status::SUCCESS);

        engine.togglePlayer(); // player 2
        REQUIRE(engine.updateState("f6") == reversi::Status::SUCCESS);

        engine.togglePlayer(); // player 1
    }
}


TEST_CASE("positionCoordsToString", "[positionconversion]") {
    REQUIRE(engine.positionCoordsToString(0, 0) == "a1");
    REQUIRE(engine.positionCoordsToString(7, 0) == "h1");
    REQUIRE(engine.positionCoordsToString(0, 7) == "a8");
    REQUIRE(engine.positionCoordsToString(7, 7) == "h8");
}