# pong-game-sdl

A simple Pong game built using **SDL2**. The game is written in C and utilizes SDL for graphics, audio, and font rendering. This project is cross-platform and can be built on macOS, Linux, and Windows.

## Prerequisites

Before building the project, ensure you have the necessary dependencies installed.

### macOS
1. Install dependencies using [Homebrew](https://brew.sh/):
   ```bash
   brew install sdl2 sdl2_ttf sdl2_mixer
   ```

2. Alternatively, use the pre-included `lib` and `include` directories without installing system-wide.

### Linux
1. Install dependencies using your package manager:
   ```bash
   sudo apt-get install libsdl2-dev libsdl2-ttf-dev libsdl2-mixer-dev
   ```

2. Alternatively, use the pre-included `lib` and `include` directories.

### Windows
1. Download the required libraries from:
   - [SDL2](https://github.com/libsdl-org/SDL/releases)
   - [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf/releases)
   - [SDL2_mixer](https://github.com/libsdl-org/SDL_mixer/releases)

2. Place the `.dll` files in the same directory as your compiled executable.

---

## Project Structure

```
.
├── Makefile         # Build configuration
├── include/         # SDL header files
├── lib/             # SDL library files (.dylib, .a, or .dll)
├── src/             # Source code
├── debug/           # Compiled object files (.o) and dependency files (.d)
├── bin/             # Compiled executable
├── res/             # Resources like fonts and textures
└── README.md        # This file
```

---

## Building the Project

### macOS/Linux
1. Open a terminal and navigate to the project directory.
2. Run the following command:
   ```bash
   make
   ```

This will:
- Compile all `.c` files into `.o` files stored in the `debug/` directory.
- Link the object files and create an executable in the `bin/` directory.

### Windows
1. Use [MinGW](https://www.mingw-w64.org/) or a similar toolchain to build the project:
   ```bash
   mingw32-make
   ```
2. Ensure the `.dll` files for SDL, SDL_ttf, and SDL_mixer are in the same directory as the executable.

---

## Running the Game

### macOS/Linux
Run the game using:
```bash
./bin/paddle_game
```

### Windows
Double-click the compiled executable (`bin\paddle_game.exe`) or run it from the terminal:
```cmd
bin\paddle_game.exe
```

---

## Cleaning the Project

To remove all compiled files and binaries:

```bash
make clean
```

This will delete the `bin/` and `debug/` directories.

## License

This Pong game is released under the [MIT License](LICENSE). Feel free to modify and distribute the code.
