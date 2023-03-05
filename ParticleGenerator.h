//
// Created by User on 28/02/2023.
//

#ifndef PARTICLESIMULATOR_PARTICLEGENERATOR_H
#define PARTICLESIMULATOR_PARTICLEGENERATOR_H

#include <vector>
#include <map>
#include "Particle.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Enumerators.h"
#include "MapSort.h"
#include "BinaryTree.h"
#include "VectorMath.h"
#include "ParticleSimulatorSettings.h"
#include "DeltaTime.h"

class ParticleGenerator {
private:
    int numOfParticlesToGenerate;
    std::vector<Particle> particles = std::vector<Particle>();
    Framework* fw;
    Vector2* gravity;
public:
    ParticleGenerator(int numOfParticles_, Vector2* gravity_, Framework* fw_) : numOfParticlesToGenerate(numOfParticles_), gravity(gravity_), fw(fw_){};

    void GenerateParticles();
    void GenerateParticles(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange);
    void GenerateParticle();
    void GenerateParticle(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange);
    void GenerateParticle(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange, Colour colour_);

    void InstantParticleGeneration(ParticleSimulatorSettings* simulatorSettings);
    void GradualParticleGeneration(int& timeOfLastSpawn, int time_, ParticleSimulatorSettings* simulatorSettings);

    void UpdateParticles(float deltaTime, CollisionPhysicsTypes collisionPhysicsType, int physicsSteps, bool shouldRender,
                         int gridSpaceCols, int gridSpaceRows, bool showImpact);

    void AddParticle(Particle particle);
    void UpdateParticleCollisionsBrute();
    void UpdateParticleCollisionsSweepNPrune();
    void UpdateParticleCollisionsUniformGridSpacePartitioning(int gridSpaceCols, int gridSpaceRows);
    //void UpdateParticleCollisionsBoundingVolumeHierarchies();

    int GetParticleCount();
};


#endif //PARTICLESIMULATOR_PARTICLEGENERATOR_H
