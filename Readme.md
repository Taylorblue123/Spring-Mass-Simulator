# Spring-Mass Simulator

Both simulators, CannonSimulator and StringSimulator, are implemented in MSVC 2022 C++. We divide the simulation calculations and rendering into two parts. The physical modeling and numerical calculations are written in C++ (using the Euler Method, Midpoint Method, and RK4 Method). The rendering module relies on the OpenGL API along with GLFW, GLM, GLAD, and ImGui libraries. To build the executable, the user needs to download all the required libraries and link them in their MSVC environment.

## Features

- Use the UI panel to input parameters and press "Fire" to start the simulation
- Select different numerical integration methods
- Press Esc to release mouse camera control to interact with the panel; press Esc again to regain camera control
- Use WSAD keys to navigate within the world

## Build Steps

1. Download and install MSVC 2022
2. Download and link the following libraries:
   - OpenGL
   - GLFW
   - GLM
   - GLAD
   - ImGui
3. Configure the project in the MSVC environment and build

## Controls

- **Esc**: Release/regain mouse camera control
- **WSAD**: Navigate within the world