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
#include "ParticleSimulatorSettings.h"

/* BUGS
 * Render Engine is Slow as Hell
 */

/* TODO
 *  Implement a way to store spawn settings to be loaded and used
 */

// Particle Simulator Settings
ParticleSimulatorSettings simulatorSettings;

// Variables
int time_ = 0;
int timeOfLastSpawn = 0;

int main(int argc, char* args[]) {

    // Create the particle simulator settings
    simulatorSettings = ParticleSimulatorSettings(R"(C:\Users\User\Desktop\Portfolio\ParticleSimulator\cmake-build-debug\SimulatorSettings\Test2.txt)");
    //simulatorSettings = ParticleSimulatorSettings();
    //simulatorSettings.SaveSimulatorSettings();

    // Create the framework class/object
    Framework fw(simulatorSettings.viewWidth, simulatorSettings.viewHeight);

    // Create an event variable
    SDL_Event event;

    // Create a new Particle Generator
    ParticleGenerator particleGenerator = ParticleGenerator(simulatorSettings.numOfParticles, &simulatorSettings.gravity, &fw);

    if(simulatorSettings.generationType == Instant) {
        if (simulatorSettings.detailedParticles) {
            particleGenerator.GenerateParticles(simulatorSettings.positionRange, simulatorSettings.velocityRange,
                                                simulatorSettings.sizeRange, simulatorSettings.massRange,
                                                simulatorSettings.elasticityRange,
                                                simulatorSettings.frictionRange); // Generates Detailed Particles
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
        if(simulatorSettings.generationType == Gradual) {

            // Check if a particle should spawn
            if((DeltaTime(timeOfLastSpawn) >= (1.0/simulatorSettings.spawnsPerSecond)) && particleGenerator.GetParticleCount() < simulatorSettings.numOfParticles) {

                if (simulatorSettings.detailedParticles) {
                    particleGenerator.GenerateParticle(simulatorSettings.positionRange, simulatorSettings.velocityRange,
                                                       simulatorSettings.sizeRange, simulatorSettings.massRange,
                                                       simulatorSettings.elasticityRange,
                                                       simulatorSettings.frictionRange); // Generates Detailed Particles
                    timeOfLastSpawn = time_;
                } else {
                    particleGenerator.GenerateParticle(); // Generates regular particles
                    timeOfLastSpawn = time_;
                }
            }
        }

        // Update the Particles
        particleGenerator.UpdateParticles(deltaTime, simulatorSettings.collisionPhysicsType,
                                          simulatorSettings.physicsSteps, simulatorSettings.shouldRender,
                                          simulatorSettings.gridSpaceCols, simulatorSettings.gridSpacesRows,
                                          simulatorSettings.showImpact);

        // Update Graphics
        fw.GraphicsUpdate();

        // Detect closure of application
        SDL_Delay(10); // Set some delay
        SDL_PollEvent(&event); // Catch the poll event

        fw.ClearGraphics(); // Clear graphics to prepare for next frame
    }

    return 0;
}
