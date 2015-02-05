# C++ Reversi Implementation

Includes a Console Reversi Game implementation, a Reversi Game Engine, and Game Engine unit tests.


## Engine

Game engine must be connected to a view object using
the engine's `setView` method. View class must inherit
from the abstract `ViewInterface` class. The engine and
view communicate via a limited public API (see `Engine/Engine.h`
and `Engine/ViewInterface.h`).

Example usage:

```
reversi::Engine game;
ViewImplementation view;

game.setView(&view);
game.runGame();
```


## View Interface

Concrete game view class must inherit from the abstract `ViewInterface` class.

Each view interface method is passed a reference to the
game engine. See `Engine/Engine.h` for public Engine
methods accessible from this reference.


## Console Reversi Game

The Console Reversi Game application begins in `ConsoleReversi/main.cpp`.
This application adds an `EasyComputerPlayer` class (inherits from `PlayerInterface`).
Player 1 or Player 2 (or both) may be set to a computer player in the game.
EasyComputerPlayer simply chooses at random from all available valid moves.


## Unit Tests

Engine unit tests begin in `UnitTests/tests.cpp`.

Unit tests use the `TestEngine` class, which inherites from `Engine` and exposes the protected class methods.