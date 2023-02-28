//
// Created by User on 28/02/2023.
//

#include "ParticleGenerator.h"

void ParticleGenerator::GenerateParticles(){

    // Generate the particles
    for (int i = 0; i < numOfParticles; i++){

        Particle p = Particle(Vector2(RandomInt(-(fw->GetWidth() / 2), fw->GetWidth() / 2),
                                      RandomInt(-(fw->GetHeight() / 2), fw->GetHeight() / 2)), gravity);
        particles.push_back(p);
    }
}

void ParticleGenerator::GenerateParticles(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange) {

    // Generate the particles
    for (int i = 0; i < numOfParticles; i++){

        Vector2 position = Vector2(RandomInt(positionRange.GetX(), positionRange.GetZ()),
                              RandomInt(positionRange.GetY(), positionRange.GetW()));

        Vector2 velocity = Vector2(RandomInt(velocityRange.GetX(), velocityRange.GetZ()),
                                   RandomInt(velocityRange.GetY(), velocityRange.GetW()));;

        int size = RandomInt(sizeRange.GetX(), sizeRange.GetY());
        int mass = RandomInt(massRange.GetX(), massRange.GetY());
        float elasticity = RandomFloat(elasticityRange.GetX(), elasticityRange.GetY(), 5);
        float friction = RandomFloat(frictionRange.GetX(), frictionRange.GetY(), 5);

        Particle p = Particle(position, velocity, size, mass, elasticity, friction, gravity);
        particles.push_back(p);
    }
}

void ParticleGenerator::UpdateParticles(float deltaTime) {

    for(int i = 0; i < particles.size(); i++){

        particles[i].UpdateParticle(fw, deltaTime);
    }
}
