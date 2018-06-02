cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Engine/Ai/AiPlayerTimed.cpp
        Engine/Ai/AiPlayerTimed.h
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
add_executable(reversi_pit ${SOURCE_FILES} ConsoleReversi/pit.cpp)
