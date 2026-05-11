# 🐍 Snake Game

Classic Snake game implemented in C++ with cross-platform support.

## Features

- Smooth console rendering
- Score tracking
- Wall and self-collision detection
- Snake grows when eating food
- Supports both keyboard layouts (WASD and Arrow keys)

## Requirements

- CMake 3.10+
- C++17 compiler
- **Linux**: ncurses library (`sudo apt-get install libncurses-dev`)
- **Windows**: Visual Studio or MinGW

## Build & Run

```bash
git clone https://github.com/dimaafanasev007/SnakeGame.git
cd SnakeGame
mkdir build && cd build
cmake ..
cmake --build .