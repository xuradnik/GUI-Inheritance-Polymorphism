# GUI-Inheritance-Polymorphism
Turtlepreter is a graphical command interpreter application designed to demonstrate object-oriented programming concepts, specifically **Inheritance** and **Polymorphism**, in C++.

## Purpose

The main goal of this project is to serve as an educational tool for learning:
- **Inheritance**: Creating specialized classes (like `Turtle`, `Runner`, `Swimmer`) from base classes (`Controllable`, `Perk`).
- **Polymorphism**: Using virtual functions and interfaces (like `ICommand`) to treat different objects uniformly.
- **Design Patterns**: Implementing patterns such as Composite (for command structures), Command, and Interpreter.

## Features

- **Visual Interpreter**: Executes commands to move and control characters on a 2D canvas.
- **Command Tree**: Commands are organized in a hierarchical tree structure, allowing for complex execution flows.
- **Multiple Characters**: Supports different types of controllable characters:
  - **Turtle**: Standard drawing turtle.
  - **Runner**: Uses stamina to move.
  - **Swimmer**: Uses oxygen to move.
- **Interactive GUI**: Built with `friimgui` (a wrapper around ImGui) to visualize the execution state and control the interpreter.

## Building and Running

### Prerequisites
- C++20 compatible compiler
- CMake (3.19 or higher)
- OpenGL

### Build Instructions
1. Clone the repository.
2. Ensure the `lib` directory containing dependencies (`friimgui`, `heap`) is present.
3. Run the following commands:

```bash
mkdir build
cd build
cmake ..
cmake --build .
./turtlepreter/turtlepreter
```

## Project Structure

- `turtlepreter/`: Source code for the application.
  - `main.cpp`: Entry point.
  - `interpreter.cpp/hpp`: Core logic for interpreting command trees.
  - `turtle.cpp/hpp`: Turtle character implementation.
  - `perk.cpp/hpp`: Runner and Swimmer implementations.
  - `controllable.cpp/hpp`: Base class for all controllable objects.
  - `turtle_gui.cpp/hpp`: GUI implementation.
- `lib/`: External dependencies (`friimgui`, `heap`).
- `resources/`: Assets (images, config).
