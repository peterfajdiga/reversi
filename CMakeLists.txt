cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Engine/Ai/Abstract/heuristics.cpp
        Engine/Ai/Abstract/heuristics.h
        Engine/Ai/Abstract/AiEvaluationPlayer.cpp
        Engine/Ai/Abstract/AiEvaluationPlayer.h
        Engine/Ai/Abstract/AiPlayerTimed.cpp
        Engine/Ai/Abstract/AiPlayerTimed.h
        Engine/Ai/AiHeuristicPlayer.cpp
        Engine/Ai/AiHeuristicPlayer.h
        Engine/Ai/AlphaBetaPlayer.cpp
        Engine/Ai/AlphaBetaPlayer.h
        Engine/Ai/EasyComputerPlayer.cpp
        Engine/Ai/EasyComputerPlayer.h
        Engine/Ai/MonteCarloPlayer.cpp
        Engine/Ai/MonteCarloPlayer.h
        Engine/Containers/Board.cpp
        Engine/Containers/Board.h
        Engine/Containers/Direction.h
        Engine/Containers/Tile.cpp
        Engine/Containers/Tile.h
        Engine/constants.h
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/helpers.h
        Engine/HumanPlayer.cpp
        Engine/HumanPlayer.h
        Engine/PlayerInterface.cpp
        Engine/PlayerInterface.h
        Engine/ViewInterface.cpp
        Engine/ViewInterface.h
        ConsoleReversi/ConsoleView.cpp
        ConsoleReversi/ConsoleView.h)

project(reversi)
add_executable(reversi ${SOURCE_FILES} ConsoleReversi/main.cpp)

project(reversi_pit)
add_executable(reversi_pit ${SOURCE_FILES} pit/pit.cpp pit/NullView.cpp pit/NullView.h)
