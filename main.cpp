#include <iostream>
#include <SDL.h>
#include "Random.h"
#include "VectorMath.h"
#include "Framework.h"
#include "DeltaTime.h"
#include "Particle.h"
#include "ParticleGenerator.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Enumerators.h"

/* Bugs
 * Render Engine is Slow as Hell
 */

// Global Parameter
int viewWidth = 1200;
int viewHeight = 600;
Vector2 gravity = Vector2(0, -9.8); // Gravity Breaks Simulation

// Particle Generation Parameters
CollisionPhysicsTypes collisionPhysicsType = SweepNPrune;
int physicsSteps = 24; // Number of collision checks per frame
bool shouldRender = true;
bool detailedParticles = true;
int numOfParticles = 100;

Vector4 positionRange = Vector4(-(viewWidth/2), -(viewHeight/2), (viewWidth/2), (viewHeight/2));
Vector4 velocityRange = Vector4(-50, -50, 50, 50);
Vector2 sizeRange = Vector2(10, 75);
Vector2 massRange = Vector2(5, 10);
Vector2 elasticityRange = Vector2(1, 1);
Vector2 frictionRange = Vector2(0.1, 0.2);

// Variables
int time_ = 0;

int main(int argc, char* args[]) {

    // Create the framework class/object
    Framework fw(viewWidth, viewHeight);

    // Create an event variable
    SDL_Event event;

    // Create a new Particle Generator
    ParticleGenerator particleGenerator = ParticleGenerator(numOfParticles, &gravity, &fw);
    if (detailedParticles){
        particleGenerator.GenerateParticles(positionRange, velocityRange, sizeRange, massRange, elasticityRange, frictionRange); // Generates Detailed Particles
    }else {
        particleGenerator.GenerateParticles(); // Generates regular particles
    }

    // Check to see if the window is ever closed and if so terminate the program
    time_ = CurrentTime();
    while(event.type != SDL_QUIT){

        // Time Management
        float deltaTime = DeltaTime(time_); // Calculate the Delta Time
        time_ = CurrentTime(); // Set the Current Time
        fw.UpdateTitle(deltaTime); // Update the title to include FPS

        // Update the Particles
        particleGenerator.UpdateParticles(deltaTime, collisionPhysicsType, physicsSteps, shouldRender);

        // Update Graphics
        fw.GraphicsUpdate();

        // Detect closure of application
        SDL_Delay(10); // Set some delay
        SDL_PollEvent(&event); // Catch the poll event

        fw.ClearGraphics(); // Clear graphics to prepare for next frame
    }

    return 0;
}
