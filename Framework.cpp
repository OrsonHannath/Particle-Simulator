//
// Created by User on 26/02/2023.
//

#include "Framework.h"

// Constructor for Framework Class
Framework::Framework(int width_, int height_) : height(height_), width(width_){

    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL as Video
    SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer); // Create the window and renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set the draw colour to black
    SDL_RenderClear(renderer); // Clear the renderer
    SDL_RenderPresent(renderer); // Update the renderer
}

// Destructor for Framework Class
Framework::~Framework() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Framework::GraphicsUpdate() {

    SDL_RenderPresent(renderer); // Update the graphics
}

void Framework::ClearGraphics() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set the draw colour to black
    SDL_RenderClear(renderer); // Clear the renderer
}

// Returns the x and y position converted from SDL2 framework space to world space
Vector2 Framework::WorldSpaceToFrameworkSpace(int xPos, int yPos){

    return Vector2(xPos + (width/2), -(yPos - (height/2)));
}

// Returns the x and y position converted from SDL2 framework space to world space
Vector2 Framework::WorldSpaceToFrameworkSpace(Vector2 pos_){

    return Vector2(pos_.GetX() + (width/2), -pos_.GetY());
}

void Framework::DrawCircle(int xPos, int yPos, int size, Colour colour) {

    // Convert the position from world space to framework space
    Vector2 pos = WorldSpaceToFrameworkSpace(xPos, yPos);

    // Set the render color for this drawing
    SDL_SetRenderDrawColor(renderer, colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

    // Draw each pixel of the circle
    for (int x = pos.GetX() - (int)(size/2); x <= pos.GetX() + (int)(size/2); x++){
        for(int y = pos.GetY() - (int)(size/2); y <= pos.GetY() + (int)(size/2); y++){

            // Make sure that the point falls within the bounds of our circle
            if((std::pow(pos.GetY() - y, 2) + std::pow(pos.GetX() - x, 2)) <= std::pow(size/2, 2)){

                // Draw the pixel to the screen
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void Framework::DrawSquare(int xPos, int yPos, int width_, int height_, Colour colour) {

    // Convert the position from world space to framework space
    Vector2 pos = WorldSpaceToFrameworkSpace(xPos, yPos);

    // Set the render color for this drawing
    SDL_SetRenderDrawColor(renderer, colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

    // Draw each pixel of the circle
    for (int x = pos.GetX() - (int)(width_/2); x <= pos.GetX() + (int)(width_/2); x++){
        for(int y = pos.GetY() - (int)(height_/2); y <= pos.GetY() + (int)(height_/2); y++){

            // Draw the pixel to the screen
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void Framework::DrawSquare(int xPos, int yPos, float size, Colour colour) {

    // Convert the position from world space to framework space
    Vector2 pos = WorldSpaceToFrameworkSpace(xPos, yPos);

    // Set the render color for this drawing
    SDL_SetRenderDrawColor(renderer, colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

    // Draw each pixel of the circle
    for (int x = pos.GetX() - (int)(size/2); x <= pos.GetX() + (int)(size/2); x++){
        for(int y = pos.GetY() - (int)(size/2); y <= pos.GetY() + (int)(size/2); y++){

            // Draw the pixel to the screen
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void Framework::DrawLine(int sXPos, int sYPos, int eXPos, int eYPos, int thickness, Colour colour) {


}

int Framework::GetWidth() {

    return width;
}

int Framework::GetHeight() {

    return height;
}
