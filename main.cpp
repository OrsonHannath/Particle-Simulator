#include <iostream>
#include <SDL.h>
#include <cmath>
#include "windows.h"
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
#include "SDLText.h"
#include <stdio.h>

/* BUGS
 * Render Engine is Slow as Hell
 */

/* TODO
 *  Implement a saving and loading UX
 *  Optimize rendering such that pixels are not drawn directly to renderer one by one
 */

// Particle Simulator Settings
ParticleSimulatorSettings simulatorSettings;

// Rendering Settings
RenderType renderType = Saved;
int renderFPS = 60;
int frameNum = 0;
int renderRuntime = 20; // Time to run simulation in seconds (Time passed after all particles spawned)

// Variables
int time_ = 0;
int timeOfLastSpawn = 0;
float timeSinceAllSpawned = 0;
bool allSpawned = false;
SDL_Event mainEvent;
HWND windowHandler;
std::string fontPath = R"(C:\Users\User\Desktop\Portfolio\ParticleSimulator\fonts\VCR_OSD_MONO_1.001.ttf)";

int main(int argc, char* args[]) {

    // Create the particle simulator settings
    simulatorSettings = ParticleSimulatorSettings(R"(C:\Users\User\Desktop\Portfolio\ParticleSimulator\cmake-build-debug\SimulatorSettings\Fountain500.txt)");
    //simulatorSettings = ParticleSimulatorSettings();
    //simulatorSettings.SaveSimulatorSettings();

    // Initialize the SDL_TTF
    if (TTF_Init() == -1){
        std::cerr << "Failed to initialize SDL_ttf!" << std::endl;
    }

    // Create the framework class/object
    Framework fw(simulatorSettings.viewWidth, simulatorSettings.viewHeight);

    // Create an event variable
    SDL_Event event;

    // Create a new Particle Generator
    ParticleGenerator particleGenerator = ParticleGenerator(simulatorSettings.numOfParticles, &simulatorSettings.gravity, &fw);

    // If Generation is Instant Call to Instantly Generate Particles
    if(simulatorSettings.generationType == Instant) {
        particleGenerator.InstantParticleGeneration(&simulatorSettings);
        allSpawned = true;
    }

    // Check to see if the window is ever closed and if so terminate the program
    time_ = CurrentTime();
    timeOfLastSpawn = CurrentTime();
    while(event.type != SDL_QUIT){

        // Time Management
        float deltaTime = DeltaTime(time_); // Calculate the Delta Time
        float deltaTimeTrue = deltaTime; // True Calculated Delta time in all instances of simulation (Doesn't account for set framerate rendering)
        time_ = CurrentTime(); // Set the Current Time
        fw.UpdateTitle(deltaTime); // Update the title to include FPS

        // If renderType is Saved then set delta time to be 1/targetFPS
        if (renderType == Saved){

            deltaTime = 1.0/renderFPS;
        }

        // If all particles have been spawned increment the timeSinceAllSpawned
        if (allSpawned){
            timeSinceAllSpawned += deltaTime;
        }

        // Update background text information
        fw.UpdateTextInformation(deltaTimeTrue, simulatorSettings.physicsSteps, simulatorSettings.simName, fontPath);

        // If Gradual Generation Setting Gradually Generate Particles
        if(simulatorSettings.generationType == Gradual) {
            particleGenerator.GradualParticleGeneration((int &)timeOfLastSpawn, time_, &simulatorSettings);

            if(particleGenerator.GetParticleCount() >= simulatorSettings.numOfParticles){

                allSpawned = true;
            }
        }

        // Update the Particles
        particleGenerator.UpdateParticles(deltaTime, simulatorSettings.collisionPhysicsType,
                                          simulatorSettings.physicsSteps, simulatorSettings.shouldRender,
                                          simulatorSettings.gridSpaceCols, simulatorSettings.gridSpacesRows,
                                          simulatorSettings.showImpact);

        // Update Graphics
        if(renderType == Realtime){

            fw.GraphicsUpdate();
        }else if (renderType == Saved){

            fw.GraphicsUpdate();
            fw.SaveFrame(simulatorSettings.simName, frameNum);
            frameNum++;
        }

        if(timeSinceAllSpawned >= renderRuntime){
            std::cout << "Render Complete" << std::endl;
            break;
        }

        // Detect closure of application
        SDL_Delay(10); // Set some delay
        SDL_PollEvent(&event); // Catch the poll event

        fw.ClearGraphics(); // Clear graphics to prepare for next frame
    }

    return 0;
}
