#include "NullView.h"


void NullView::setupGame() {

}

void NullView::teardownGame() {

}

void NullView::displayState(bool isGameOver) {

}

void NullView::displayStatus(reversi::Status status) {

}

reversi::Tile NullView::getMoveInput() {
    throw 1234;
}

void NullView::onGameOver() {

}
