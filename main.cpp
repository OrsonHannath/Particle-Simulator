#include <iostream>
#include <SDL.h>
#include "Framework.h"

int main(int argc, char* args[]) {

    // Create the framework class/object
    Framework fw(600, 1200);

    // Create an event variable
    SDL_Event event;

    fw.DrawCircle(600, 300, 90, Colour(255, 255, 255, 255));
    fw.DrawSquare(600, 300, 50, 40, Colour(65, 189, 65, 255));
    fw.DrawSquare(600, 300, 20, Colour(10, 60, 90, 255));

    // Check to see if the window is ever closed and if so terminate the program
    while(event.type != SDL_QUIT){

        fw.GraphicsUpdate();

        SDL_Delay(10); // Set some delay
        SDL_PollEvent(&event); // Catch the poll event
    }

    return 0;
}
