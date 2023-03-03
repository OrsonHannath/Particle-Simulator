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

/* BUGS
 * Render Engine is Slow as Hell
 */

/* TODO
 *  Implement a way to store spawn settings to be loaded and used
 */

// Global Parameter
int viewWidth = 1200;
int viewHeight = 600;
Vector2 gravity = Vector2(0, -9.8); // Gravity Breaks Simulation

// Particle Generation Parameters
CollisionPhysicsTypes collisionPhysicsType = UniformGridSpacePartitioning;
GenerationTypes generationType = Gradual;
bool loadSpawnSettings = false; // Should the settings be loaded from file
std::string settingsPath = ""; // Location of settings file
int physicsSteps = 16; // Number of collision checks per frame
bool shouldRender = true; // Should the particles be rendered
bool detailedParticles = true; // Should particles be spawned with all parameters set
bool showImpact = false; // Should particles flash on impact
int numOfParticles = 20; // Number of particles to spawn in
float spawnsPerSecond = 4; // Number of particles to spawn per second when in gradual mode
int gridSpaceCols = 12; // Number of Grid space Columns
int gridSpacesRows = 6; // Number of Grid Space Rows

// Particle Spawn Settings
Vector4 positionRange = Vector4(-(viewWidth/2), -(viewHeight/2), (viewWidth/2), (viewHeight/2));
Vector4 velocityRange = Vector4(-50, -50, 50, 50);
Vector2 sizeRange = Vector2(10, 12);
Vector2 massRange = Vector2(5, 10);
Vector2 elasticityRange = Vector2(1, 1);
Vector2 frictionRange = Vector2(0.1, 0.2);

// Variables
int time_ = 0;
int timeOfLastSpawn = 0;

int main(int argc, char* args[]) {

    // Create the framework class/object
    Framework fw(viewWidth, viewHeight);

    // Create an event variable
    SDL_Event event;

    // Create a new Particle Generator
    ParticleGenerator particleGenerator = ParticleGenerator(numOfParticles, &gravity, &fw);

    if(generationType == Instant) {
        if (detailedParticles) {
            particleGenerator.GenerateParticles(positionRange, velocityRange, sizeRange, massRange, elasticityRange,
                                                frictionRange); // Generates Detailed Particles
        } else {
            particleGenerator.GenerateParticles(); // Generates regular particles
        }
    }

    // Check to see if the window is ever closed and if so terminate the program
    time_ = CurrentTime();
    timeOfLastSpawn = CurrentTime();
    while(event.type != SDL_QUIT){

        // Time Management
        float deltaTime = DeltaTime(time_); // Calculate the Delta Time
        time_ = CurrentTime(); // Set the Current Time
        fw.UpdateTitle(deltaTime); // Update the title to include FPS

        // If Gradual Generation Setting Gradually Generate Particles
        if(generationType == Gradual) {

            // Check if a particle should spawn
            if((DeltaTime(timeOfLastSpawn) >= (1.0/spawnsPerSecond)) && particleGenerator.GetParticleCount() < numOfParticles) {

                if (detailedParticles) {
                    particleGenerator.GenerateParticle(positionRange, velocityRange, sizeRange, massRange,
                                                        elasticityRange, frictionRange); // Generates Detailed Particles
                    timeOfLastSpawn = time_;
                } else {
                    particleGenerator.GenerateParticle(); // Generates regular particles
                    timeOfLastSpawn = time_;
                }
            }
        }

        // Update the Particles
        particleGenerator.UpdateParticles(deltaTime, collisionPhysicsType, physicsSteps, shouldRender, gridSpaceCols, gridSpacesRows, showImpact);

        // Update Graphics
        fw.GraphicsUpdate();

        // Detect closure of application
        SDL_Delay(10); // Set some delay
        SDL_PollEvent(&event); // Catch the poll event

        fw.ClearGraphics(); // Clear graphics to prepare for next frame
    }

    return 0;
}
