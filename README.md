# Explosion of Particles

## Overview

**Explosion of Particles** is an engaging visual simulation developed using C++ and SDL2, which produces an explosive visual effect, illustrating particles as they interact and move across the screen. 

## Goals and Objectives

The primary goal of this project is to deepen the understanding of computer graphics through practical application. By manipulating colors at the byte level, we effectively use bitwise operations to create vivid visual effects. The application is built around the concept of particles—tiny visual elements that move in a two-dimensional space—simulating natural phenomena.

Key features include:

- **Bit Manipulation**: The project utilizes bitwise operations for color composition, enabling precise control over the RGBA (Red, Green, Blue, Alpha) values of each pixel. This approach helps to create smooth transitions and vibrant colors in the simulation.

- **Color Representation**: The simulation employs a palette of colors generated through a combination of red, green, and blue channels. Each particle can have a unique color, enhancing the visual appeal and complexity of the explosion effect.

- **SDL2 Integration**: Leveraging the Simple DirectMedia Layer (SDL2), the project handles graphics rendering, input processing, and resource management efficiently. 

- **C++ Implementation**: The entire simulation is written in C++, showcasing object-oriented programming principles. Key classes such as `Particle`, `Screen`, and `Swarm` encapsulate functionality and enable modular design, promoting code reuse and maintainability.

## Getting Started

To compile and run the project, git clone into my repository and compile it using `g++ -Isrc/Include -Lsrc/lib -o explosion main.cpp Screen.cpp Swarm.cpp Particle.cpp -lmingw32 -lSDL2main -lSDL2` 
