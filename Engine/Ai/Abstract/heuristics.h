#pragma once

#include "../../Containers/Board.h"


namespace reversi::heuristics {

    double stanford(const Board& board);

    double stanford_modified(const Board& board);

    double stanford_modified_4_8(const Board& board);

    double moves(const Board& board);

    double stability(const Board& board);

    double stability_old(const Board& board);

};
