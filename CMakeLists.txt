cmake_minimum_required(VERSION 3.9)
project(reversi)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Engine/Containers/Board.cpp
        Engine/Containers/Board.h
        Engine/Containers/Direction.h
        Engine/Containers/Tile.cpp
        Engine/Containers/Tile.h
        Engine/constants.h
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/HumanPlayer.cpp
        Engine/HumanPlayer.h
        Engine/PlayerInterface.cpp
        Engine/PlayerInterface.h
        Engine/ViewInterface.cpp
        Engine/ViewInterface.h
        ConsoleReversi/ConsoleView.cpp
        ConsoleReversi/ConsoleView.h
        Engine/Ai/EasyComputerPlayer.cpp
        Engine/Ai/EasyComputerPlayer.h
        ConsoleReversi/main.cpp)

add_executable(reversi ${SOURCE_FILES})
