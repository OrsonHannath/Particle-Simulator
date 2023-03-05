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
    SDL_RenderClear(renderer);
}

// Destructor for Framework Class
Framework::~Framework() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Framework::GraphicsUpdate() {

    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);
    SDL_RenderPresent(renderer); // Update the graphics
}

void Framework::ClearGraphics() {

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0); // Set the draw colour to black
    SDL_RenderClear(renderer); // Clear the renderer
}

void Framework::UpdateTitle(float deltaTime) {

    int fps = 1/(deltaTime);
    std::string title = "Particle Simulator: " + std::to_string(fps) + "fps";
    SDL_SetWindowTitle(window, title.c_str());
}

void Framework::UpdateTextInformation(float deltaTime, int physicsSteps, std::string simTitle, std::string &fontPath) {

    Colour textCol = Colour(255, 255, 255, 255);
    Colour titleCol = Colour(128, 0, 255, 255);

    // Graphics Frame MS and FPS
    SDLText msGraphics = SDLText(std::to_string((int)(deltaTime * 1000)) + "ms - Graphics Updates - " + std::to_string((int)(1/deltaTime)) + "fps", 12, textCol, fontPath, renderer);
    msGraphics.Display(Center, (width/2), (height/10) + 35, renderer);

    // Physics Frame MS and FPS
    SDLText msPhysics = SDLText(FloatToString(((float)deltaTime * 1000 / physicsSteps), 2) + "ms - Physics Updates - " + std::to_string((int)(1.0/(deltaTime / physicsSteps))) + "fps", 12, textCol, fontPath, renderer);
    msPhysics.Display(Center, (width/2), (height/10) + 50, renderer);

    // Simulation Title
    SDLText title = SDLText(simTitle, 50, titleCol, fontPath, renderer);
    title.Display(Center, (width/2), (height/10), renderer);
}

void Framework::SaveFrame(std::string& simName, int frameNumber){

    // Determine the path that the exe is being run from
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH);
    std::string currentDirectory = std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/"));
    std::string directory = currentDirectory + "/SimulatorRenders/";
    std::string directoryFull = currentDirectory + "/SimulatorRenders/" + simName + "/";

    // Create the directory at given location
    CreateDirectory(directory.c_str(), NULL);
    CreateDirectory(directoryFull.c_str(), NULL);

    // Copy the renderer as a surface
    SDL_Surface *surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
    SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

    // Try to save to PNG
    if(IMG_SavePNG(surface, (directoryFull + std::to_string(frameNumber) + ".png").c_str()) != 0) {
        // Error saving bitmap
        printf("SDL_SaveBMP failed: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface);
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

void DrawText(int xPos, int yPos, int size, Colour colour){


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

SDL_Window* Framework::GetWindow(){

    return window;
}

SDL_Renderer* Framework::GetRenderer(){

    return renderer;
}
