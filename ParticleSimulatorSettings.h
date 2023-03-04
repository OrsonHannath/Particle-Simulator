//
// Created by User on 3/03/2023.
//

#ifndef PARTICLESIMULATOR_PARTICLESIMULATORSETTINGS_H
#define PARTICLESIMULATOR_PARTICLESIMULATORSETTINGS_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include "unistd.h"
#include "Vector4.h"
#include "Vector2.h"
#include "Framework.h"
#include "Enumerators.h"

class ParticleSimulatorSettings {
public:
    ParticleSimulatorSettings()= default;
    ParticleSimulatorSettings(std::string settingsLocation);

    std::string simName = "Fountain500";

    int viewWidth = 1200;
    int viewHeight = 600;
    Vector2 gravity = Vector2(0, -9.8); // Gravity Breaks Simulation

    CollisionPhysicsTypes collisionPhysicsType = UniformGridSpacePartitioning;
    GenerationTypes generationType = Gradual;
    ColourTypes colourType = Lerp;

    int physicsSteps = 16; // Number of collision checks per frame
    bool shouldRender = true; // Should the particles be rendered
    bool detailedParticles = true; // Should particles be spawned with all parameters set
    bool showImpact = false; // Should particles flash on impact
    int numOfParticles = 500; // Number of particles to spawn in
    float spawnsPerSecond = 20; // Number of particles to spawn per second when in gradual mode
    int gridSpaceCols = 12; // Number of Grid space Columns
    int gridSpacesRows = 6; // Number of Grid Space Rows
    Colour specificColour = Colour(128, 24, 172, 255); // Colour for specific setting
    Colour lerpStartColour = Colour(30, 10, 180, 255); // Colour to start lerp at
    Colour lerpEndColour = Colour(30, 10, 255, 255); // Colour to end lerp at

    Vector4 positionRange = Vector4(-(viewWidth/2.0) + 10, (viewHeight/4.0), -(viewWidth/2.0) + 10, (viewHeight/4.0));
    Vector4 velocityRange = Vector4(500, -5, 500, 5);
    Vector2 sizeRange = Vector2(10, 12);
    Vector2 massRange = Vector2(10, 10);
    Vector2 elasticityRange = Vector2(0.05, 0.1);
    Vector2 frictionRange = Vector2(0.001, 0.002);

    void SaveSimulatorSettings();

private:
    // simName, viewWidth, viewHeight, gravityX, gravityY, collisionPhysicsType, generationType, colourType, physicsSteps, shouldRender,
    // detailedParticles, showImpact, numOfParticles, spawnsPerSecond, gridSpaceCols, gridSpaceRows,
    // specificColour_r, specificColour_g, specificColour_b, specificColour_a,
    // lerpStartCol_r, lerpStartCol_g, lerpStartCol_b, lerpStartCol_a,
    // lerpEndCol_r, lerpEndCol_g, lerpEndCol_b, lerpEndCol_a,
    // positionRangeX1, positionRangeY1, positionRangeX2, positionRangeY2,
    // velocityRangeX1, velocityRangeY1, velocityRangeX2, velocityRangeY2,
    // sizeRangeX, sizeRangeY, massRangeX, massRangeY,
    // elasticityRangeX, elasticityRangeY, frictionRangeX, frictionRangeY
    const char* ParticleSimulatorSettingsFormatOut = "%s, %i, %i, %f, %f, %s, %s, %s, %d, %d, "
                                                  "%d, %d, %i, %f, %i, %i, "
                                                  "%i, %i, %i, %i, "
                                                  "%i, %i, %i, %i, "
                                                  "%i, %i, %i, %i, "
                                                  "%f, %f, %f, %f, "
                                                  "%f, %f, %f, %f, "
                                                  "%i, %i, %i, %i, "
                                                  "%f, %f, %f, %f\n";
    const char* ParticleSimulatorSettingsFormatIn = "%[^,], %i, %i, %f, %f, %[^,], %[^,], %[^,], %d, %d, "
                                                     "%d, %d, %i, %f, %i, %i, "
                                                     "%i, %i, %i, %i, "
                                                     "%i, %i, %i, %i, "
                                                     "%i, %i, %i, %i, "
                                                     "%f, %f, %f, %f, "
                                                     "%f, %f, %f, %f, "
                                                     "%i, %i, %i, %i, "
                                                     "%f, %f, %f, %f\n";
};


#endif //PARTICLESIMULATOR_PARTICLESIMULATORSETTINGS_H
