//
// Created by User on 26/02/2023.
//

#include "Framework.h"

// Constructor for Framework Class
Framework::Framework(int height_, int width_) : height(height_), width(width_){

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

    // Update the graphics
    SDL_RenderPresent(renderer);
}

void Framework::DrawCircle(int xPos, int yPos, int size, Colour colour) {

    // Set the render color for this drawing
    SDL_SetRenderDrawColor(renderer, colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

    // Draw each pixel of the circle
    for (int x = xPos - (int)(size/2); x <= xPos + (int)(size/2); x++){
        for(int y = yPos - (int)(size/2); y <= yPos + (int)(size/2); y++){

            // Make sure that the point falls within the bounds of our circle
            if((std::pow(yPos - y, 2) + std::pow(xPos - x, 2)) <= std::pow(size/2, 2)){

                // Draw the pixel to the screen
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void Framework::DrawSquare(int xPos, int yPos, int width_, int height_, Colour colour) {

    // Set the render color for this drawing
    SDL_SetRenderDrawColor(renderer, colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

    // Draw each pixel of the circle
    for (int x = xPos - (int)(width_/2); x <= xPos + (int)(width_/2); x++){
        for(int y = yPos - (int)(height_/2); y <= yPos + (int)(height_/2); y++){

            // Draw the pixel to the screen
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void Framework::DrawSquare(int xPos, int yPos, float size, Colour colour) {

    // Set the render color for this drawing
    SDL_SetRenderDrawColor(renderer, colour.GetRed(), colour.GetGreen(), colour.GetBlue(), colour.GetAlpha());

    // Draw each pixel of the circle
    for (int x = xPos - (int)(size/2); x <= xPos + (int)(size/2); x++){
        for(int y = yPos - (int)(size/2); y <= yPos + (int)(size/2); y++){

            // Draw the pixel to the screen
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

void Framework::DrawLine(int sXPos, int sYPos, int eXPos, int eYPos, int thickness, Colour colour) {


}
