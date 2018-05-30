cmake_minimum_required(VERSION 3.9)
project(reversi)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
        Engine/constants.h
        Engine/Engine.cpp
        Engine/Engine.h
        Engine/HumanPlayer.cpp
        Engine/HumanPlayer.h
        Engine/Tile.cpp
        Engine/Tile.h
        Engine/PlayerInterface.cpp
        Engine/PlayerInterface.h
        Engine/ViewInterface.cpp
        Engine/ViewInterface.h
        ConsoleReversi/ConsoleView.cpp
        ConsoleReversi/ConsoleView.h
        ConsoleReversi/EasyComputerPlayer.cpp
        ConsoleReversi/EasyComputerPlayer.h
        ConsoleReversi/main.cpp)

add_executable(reversi ${SOURCE_FILES})
