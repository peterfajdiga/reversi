#pragma once

#include "../Engine/ViewInterface.h"


class NullView : public reversi::ViewInterface {
public:
    void setupGame() override;

    void teardownGame() override;

    void displayState(bool isGameOver) override;

    void displayStatus(reversi::Status status) override;

    reversi::Tile getMoveInput() override;

    void onGameOver() override;
};
