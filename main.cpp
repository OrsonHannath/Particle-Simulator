#include <iostream>
#include <SDL.h>
#include "Random.h"
#include "VectorMath.h"
#include "Framework.h"
#include "DeltaTime.h"
#include "Particle.h"

int time_ = 0;

int main(int argc, char* args[]) {

    // Create the framework class/object
    Framework fw(1200, 600);

    // Create an event variable
    SDL_Event event;

    // Create a new particle
    Particle p1 = Particle(Vector2(0, 0), 100);
    Particle p2 = Particle(Vector2(-200, 0),200, 10, Vector2(RandomNumber(25, 100), RandomNumber(25, 100)));
    Particle p3 = Particle(Vector2(200, 0), 200, 10, Vector2(RandomNumber(25, 100), RandomNumber(25, 100)));

    // Check to see if the window is ever closed and if so terminate the program
    time_ = CurrentTime();
    while(event.type != SDL_QUIT){

        // Time Management
        float deltaTime = DeltaTime(time_); // Calculate the Delta Time
        time_ = CurrentTime(); // Set the Current Time

        // Update the Particle
        p1.UpdateParticle(&fw, deltaTime);
        p2.UpdateParticle(&fw, deltaTime);
        p3.UpdateParticle(&fw, deltaTime);

        p2.ParticleCollision(&p3);

        // Update Graphics
        fw.GraphicsUpdate();

        // Detect closure of application
        SDL_Delay(10); // Set some delay
        SDL_PollEvent(&event); // Catch the poll event

        fw.ClearGraphics(); // Clear graphics to prepare for next frame
    }

    return 0;
}
