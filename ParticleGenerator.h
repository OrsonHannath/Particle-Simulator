//
// Created by User on 28/02/2023.
//

#ifndef PARTICLESIMULATOR_PARTICLEGENERATOR_H
#define PARTICLESIMULATOR_PARTICLEGENERATOR_H

#include <vector>
#include "Particle.h"
#include "Vector2.h"
#include "Vector4.h"

class ParticleGenerator {
private:
    int numOfParticles;
    std::vector<Particle> particles = std::vector<Particle>();
    Framework* fw;
    Vector2* gravity;
public:
    ParticleGenerator(int numOfParticles_, Vector2* gravity_, Framework* fw_) : numOfParticles(numOfParticles_), gravity(gravity_), fw(fw_){};

    void GenerateParticles();
    void GenerateParticles(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange);
    void UpdateParticles(float deltaTime);
};


#endif //PARTICLESIMULATOR_PARTICLEGENERATOR_H
