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

void ParticleGenerator::UpdateParticles(float deltaTime, CollisionPhysicsTypes collisionPhysicsType, int physicsSteps, bool shouldRender) {

    // Update the particle physics n number of times in this frame
    for (int s = 0; s < physicsSteps; s++){

        float stepDeltaTime = (deltaTime / physicsSteps);

        //Update the Particles
        for(int i = 0; i < particles.size(); i++){

            particles[i].UpdateParticle(fw, stepDeltaTime);
        }

        // Update the Particles Collisions
        switch (collisionPhysicsType) {
            case Brute:
                UpdateParticleCollisionsBrute();
                break;
            case SweepNPrune:
                UpdateParticleCollisionsSweepNPrune();
                break;
            case GridSpacePartitioning:
                UpdateParticleCollisionsGridSpacePartitioning();
                break;
            case KDTrees:
                UpdateParticleCollisionsKDTrees();
                break;
            case BoundingVolumeHierarchies:
                UpdateParticleCollisionsBoundingVolumeHierarchies();
                break;
        }
    }

    // Update the particles' graphics once in this frame
    if(shouldRender) {
        for (int i = 0; i < particles.size(); i++) {

            particles[i].UpdateParticleGraphics(fw);
        }
    }
}

void ParticleGenerator::UpdateParticleCollisionsBrute(){

    // Each particle should only need to collide with another once per update
    for (int i = 0; i < particles.size(); i++){
        for (int j = 0; j < particles.size(); j++){

            if(i != j && particles[i].GetCollidedParticle() != &particles[j]){

                bool collided = particles[i].ParticleCollision(&particles[j]);
            }
        }
    }
}

void ParticleGenerator::UpdateParticleCollisionsSweepNPrune(){

    std::vector<Particle*> xPosSortedParticles;
    std::vector<Particle*> activeInterval;
    Vector2 intervalVector;
    bool activeIntervalSet = false;

    // Sort all particles based on their x position
    std::map<int, float> xPosMap; // A map that stores the particle array position as key and the particles x position as the value
    for (int i = 0; i < particles.size(); i++){

        xPosMap[i] = particles[i].GetPosition()->GetX();
    }
    std::vector<std::pair<int, float>> sortedPairsVec = SortMapByValue(xPosMap);

    // Set the xPosSortedParticles vector based on sortedPairsVec
    for (std::pair<int, float> p : sortedPairsVec){

        xPosSortedParticles.push_back(&particles[p.first]);
        //std::cout << p.second << std::endl;
    }

    // Loop through all particles to find which ones exist in the same interval across the x-axis
    for (int i = 0; i < xPosSortedParticles.size(); i++){

        // Check if there is an active interval
        if(!activeIntervalSet){

            // Set the active interval bool, add this particle to the start of the interval
            activeIntervalSet = true;
            activeInterval.clear();
            activeInterval.push_back(xPosSortedParticles[i]);

            // Set the Interval Vector for which this particle resides
            float intervalStart = xPosSortedParticles[i]->GetPosition()->GetX() - xPosSortedParticles[i]->GetRadius();
            float intervalEnd = xPosSortedParticles[i]->GetPosition()->GetX() + xPosSortedParticles[i]->GetRadius();
            intervalVector = Vector2(intervalStart, intervalEnd);

            // Continue to the next particle
            continue;
        }

        // Check if the next particle resides in this interval
        float particleIntervalStart = xPosSortedParticles[i]->GetPosition()->GetX() - xPosSortedParticles[i]->GetRadius();
        float particleIntervalEnd = xPosSortedParticles[i]->GetPosition()->GetX() + xPosSortedParticles[i]->GetRadius();
        if((particleIntervalStart <= intervalVector.GetY() && particleIntervalEnd >= intervalVector.GetX()) ||
            (particleIntervalEnd <= intervalVector.GetY() && particleIntervalStart >= intervalVector.GetX())){

            // Particle does exist in the interval so extend the interval and add it to the activeInterval
            if(particleIntervalStart <= intervalVector.GetX()){

                // Interval needs starting point adjusted
                intervalVector.SetX(particleIntervalStart);
            }
            if(particleIntervalEnd >= intervalVector.GetY()){

                // Interval needs ending point adjusted
                intervalVector.SetY(particleIntervalEnd);
            }

            // Add this particle to the activeInterval
            activeInterval.push_back(xPosSortedParticles[i]);
        }else{

            // Particle does not exist in the interval so check collision in activeInterval particles
            for (int w = 0; w < activeInterval.size(); w++){
                for (int z = 0; z < activeInterval.size(); z++){

                    if(w != z && activeInterval[w]->GetCollidedParticle() != activeInterval[z]){

                        bool collided = activeInterval[w]->ParticleCollision(activeInterval[z]);
                    }
                }
            }

            // Since this particle is not part of activeInterval start a new activeInterval with this particle
            i--;
            activeIntervalSet = false;
            continue;
        }
    }

    // Update the collisions of the final interval
    if (activeInterval.size() > 0){

        for (int w = 0; w < activeInterval.size(); w++){
            for (int z = 0; z < activeInterval.size(); z++){

                if(w != z && activeInterval[w]->GetCollidedParticle() != activeInterval[z]){

                    bool collided = activeInterval[w]->ParticleCollision(activeInterval[z]);
                }
            }
        }
    }
}

void ParticleGenerator::UpdateParticleCollisionsGridSpacePartitioning(){

}

void ParticleGenerator::UpdateParticleCollisionsKDTrees(){

}

void ParticleGenerator::UpdateParticleCollisionsBoundingVolumeHierarchies(){

}
