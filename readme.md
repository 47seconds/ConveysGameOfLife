# Conway's Game of Life

A simple implementation of Conway's Game of Life in C using SDL2 for graphics rendering.

## Table of Contents
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [How It Works](#how-it-works)
- [License](#license)

---

## Requirements

Before you can run the program, make sure you have the following installed:

1. **C Compiler**: Any C99-compatible compiler (e.g., GCC or Clang).
2. **SDL2 Library**: Install the SDL2 library to enable graphical rendering.

### Installing SDL2

#### On Linux
```bash
sudo apt-get install libsdl2-dev
```

#### On macOS
```bash
brew install sdl2
```

#### On Windows
Download and install SDL2 (version 2) from the [official website](https://github.com/libsdl-org/SDL/releases/).

---

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/47seconds/ConveysGameOfLife.git
   cd ConveysGameOfLife
   ```

2. Compile the program:
   ```bash
   gcc -o main main.c `sdl2-config --cflags --libs`
   ```
   Replace `main.c` with the actual name of the source file if it differs.

---

## Usage

Run the program with the following command:

1. If compiled:
```bash
./main
```

2. If downloaded binaries:
```bash
./ConveysGameOfLife.bin (Linux)
./ConveysGameOfLife.exe (Windows)
```

### Controls
- **Left Click**: Toggle a cell (alive/dead).
- **Spacebar**: Start/pause the simulation.
- **R**: Generate random simulation enviroment.
- **E**: Next generation for current enviroment, or run simulation frame-by-frame.
- **Enter**: Reset the grid.
- **Esc**: Quit the program.
---

## How It Works

Conway's Game of Life is a cellular automaton with the following rules:

1. **Birth**: A dead cell with exactly 3 neighbors becomes alive.
2. **Survival**: A live cell with 2 or 3 neighbors remains alive.
3. **Death**: All other cells die or remain dead.

The program displays the grid and updates it in real-time according to these rules. You can interact with the grid to create initial patterns and watch them evolve.

---

## License

This project is licensed under the [MIT License](LICENSE).

Feel free to use, modify, and distribute the code as you see fit.
