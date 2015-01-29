# C++ Reversi Implementation

Includes Reversi Game Engine, abstract Reversi Game View interface, 
Console Game View implementation, and unit tests.


## Engine

Game engine must be connected to a view object using
the engine's `setView` method. View class must inherit
from the abstract `ReversiGameView` class. The engine and
view communicate via a limited public API (see `ReversiGameEngine.h`
and `ReversiGameView.h`).

Example usage:

```
ReversiGameEngine game;
ReversiGameViewSub view;

game.setView(&view);
game.runGame();
```


## Abstract View

Concrete game view class must inherit from the abstract 
`ReversiGameView` class and must implement all pure virtual
interface methods.

Each view interface method is passed a const reference to the
game engine. See `ReversiGameEngine.h` for public view helper
methods accessible from this reference.


## Console View

The Console View application begins in `ConsoleReversi/main.cpp`.


## Unit Tests

Engine unit tests begin in `UnitTests/tests.cpp`.

Unit tests use the `ReversiGameTestEngine` class, which inherites from `ReversiGameEngine` and exposes the protected class methods.