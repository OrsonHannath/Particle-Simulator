//
// Created by User on 26/02/2023.
//
// Inspired by: https://iq.opengenus.org/getting-started-2d-graphics-in-cpp-sdl2/

#ifndef PARTICLESIMULATOR_FRAMEWORK_H
#define PARTICLESIMULATOR_FRAMEWORK_H

#include <SDL.h>
#include <cmath>
#include "Colour.h"

class Framework {
private:
    int height; // Window Height
    int width; // Window Width
    SDL_Renderer *renderer = NULL; // Pointer to Renderer
    SDL_Window *window = NULL; // Pointer to Window
public:
    Framework(int height_, int width_); // Constructor
    ~Framework(); // Destructor
    void GraphicsUpdate(); // Graphics Update

    // Drawing Functions
    void DrawCircle(int xPos, int yPos, int size, Colour colour);

    void DrawSquare(int xPos, int yPos, int width_, int height_, Colour colour);
    void DrawSquare(int xPos, int yPos, float size, Colour colour);

    void DrawLine(int sXPos, int sYPos, int eXPos, int eYPos, int thickness, Colour colour);
};


#endif //PARTICLESIMULATOR_FRAMEWORK_H
