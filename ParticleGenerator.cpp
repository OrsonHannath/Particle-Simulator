//
// Created by User on 28/02/2023.
//

#include "ParticleGenerator.h"

void ParticleGenerator::GenerateParticles(){

    // Generate the particles
    for (int i = 0; i < numOfParticlesToGenerate; i++){

        Particle p = Particle(Vector2(RandomInt(-(fw->GetWidth() / 2), fw->GetWidth() / 2),
                                      RandomInt(-(fw->GetHeight() / 2), fw->GetHeight() / 2)), gravity);
        particles.push_back(p);
    }
}

void ParticleGenerator::GenerateParticles(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange) {

    // Generate the particles
    for (int i = 0; i < numOfParticlesToGenerate; i++){

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

void ParticleGenerator::GenerateParticle(){

    // Generate the particles
    Particle p = Particle(Vector2(RandomInt(-(fw->GetWidth() / 2), fw->GetWidth() / 2),
                                      RandomInt(-(fw->GetHeight() / 2), fw->GetHeight() / 2)), gravity);
    particles.push_back(p);
}

void ParticleGenerator::GenerateParticle(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange) {

    // Generate the particle
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

void ParticleGenerator::GenerateParticle(Vector4 positionRange, Vector4 velocityRange, Vector2 sizeRange, Vector2 massRange, Vector2 elasticityRange, Vector2 frictionRange, Colour colour_) {

    // Generate the particle
    Vector2 position = Vector2(RandomInt(positionRange.GetX(), positionRange.GetZ()),
                               RandomInt(positionRange.GetY(), positionRange.GetW()));

    Vector2 velocity = Vector2(RandomInt(velocityRange.GetX(), velocityRange.GetZ()),
                               RandomInt(velocityRange.GetY(), velocityRange.GetW()));;

    int size = RandomInt(sizeRange.GetX(), sizeRange.GetY());
    int mass = RandomInt(massRange.GetX(), massRange.GetY());
    float elasticity = RandomFloat(elasticityRange.GetX(), elasticityRange.GetY(), 5);
    float friction = RandomFloat(frictionRange.GetX(), frictionRange.GetY(), 5);

    Particle p = Particle(position, velocity, size, mass, elasticity, friction, gravity);
    p.SetColour(colour_);
    particles.push_back(p);
}

void ParticleGenerator::UpdateParticles(float deltaTime, CollisionPhysicsTypes collisionPhysicsType, int physicsSteps,
                                        bool shouldRender, int gridSpaceCols, int gridSpaceRows, bool showImpact) {

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
            case UniformGridSpacePartitioning:
                UpdateParticleCollisionsUniformGridSpacePartitioning(gridSpaceCols, gridSpaceRows);
                break;
            case BoundingVolumeHierarchy:
                //UpdateParticleCollisionsBoundingVolumeHierarchies();
                break;
        }
    }

    // Update the particles' graphics once in this frame
    if(shouldRender) {
        for (int i = 0; i < particles.size(); i++) {

            particles[i].UpdateParticleGraphics(fw, showImpact);
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

// Split the screen into grid spaces that store references to particles that exist within them
void ParticleGenerator::UpdateParticleCollisionsUniformGridSpacePartitioning(int gridSpaceCols, int gridSpaceRows){

    /*
     * Potential Optimization: Loop through particles vector once and assign the particle to the grid spaces it fits within from there
     */

    std::vector<Particle*> gridParticleVectors[gridSpaceCols][gridSpaceRows];
    float gridSizeX = fw->GetWidth()/(float)gridSpaceCols;
    float gridSizeY = fw->GetHeight()/(float)gridSpaceRows;

    for(int i = 0; i < gridSpaceCols; i++){
        for(int j = 0; j < gridSpaceRows; j++){

            // Loop through all particles and check if they exist in this grid space
            for(Particle& p : particles){

                float particleXStart = p.GetPosition()->GetX() - p.GetRadius();
                float particleXEnd = p.GetPosition()->GetX() + p.GetRadius();
                float particleYStart = p.GetPosition()->GetY() - p.GetRadius();
                float particleYEnd = p.GetPosition()->GetY() + p.GetRadius();

                // Check if the particle fits within the x bounds of this grid space
                if((particleXStart >= ((gridSizeX * i) - (fw->GetWidth()/2.0)) && particleXStart <= ((gridSizeX * (i+1)) - (fw->GetWidth()/2.0))) ||
                   (particleXEnd >= ((gridSizeX * i) - (fw->GetWidth()/2.0)) && particleXEnd <= ((gridSizeX * (i+1)) - (fw->GetWidth()/2.0)))){

                    // Check if the particle fits within the y bounds of this grid space
                    if((particleYStart >= ((gridSizeY * j) - (fw->GetHeight()/2.0)) && particleYStart <= ((gridSizeY * (j+1)) - (fw->GetHeight()/2.0))) ||
                       (particleYEnd >= ((gridSizeY * j) - (fw->GetHeight()/2.0)) && particleYEnd <= ((gridSizeY * (j+1)) - (fw->GetHeight()/2.0)))){

                        // This particle belongs to this grid space
                        gridParticleVectors[i][j].push_back(&p);
                    }
                }
            }
        }
    }

    // Now that grid particle vectors have been filled update collision of all particles in each grid space
    for(int i = 0; i < gridSpaceCols; i++){
        for(int j = 0; j < gridSpaceRows; j++) {

            for(int k = 0; k < gridParticleVectors[i][j].size(); k++){
                for(int l = 0; l < gridParticleVectors[i][j].size(); l++){

                    if(k != l && gridParticleVectors[i][j][l]->GetCollidedParticle() != gridParticleVectors[i][j][l]){

                        bool collided = gridParticleVectors[i][j][k]->ParticleCollision(gridParticleVectors[i][j][l]);
                    }
                }
            }
        }
    }
}

void ParticleGenerator::InstantParticleGeneration(ParticleSimulatorSettings* simulatorSettings){

    if (simulatorSettings->detailedParticles) {
        GenerateParticles(simulatorSettings->positionRange, simulatorSettings->velocityRange,
                                            simulatorSettings->sizeRange, simulatorSettings->massRange,
                                            simulatorSettings->elasticityRange,
                                            simulatorSettings->frictionRange); // Generates Detailed Particles
    } else {
        GenerateParticles(); // Generates regular particles
    }
}

void ParticleGenerator::GradualParticleGeneration(int& timeOfLastSpawn, int time_, ParticleSimulatorSettings* simulatorSettings) {

    // Check if a particle should spawn
    if((DeltaTime(timeOfLastSpawn) >= (1.0/simulatorSettings->spawnsPerSecond)) && GetParticleCount() < simulatorSettings->numOfParticles) {

        if(simulatorSettings->colourType == Lerp) {

            float lerpPos = (float)GetParticleCount() / (float)simulatorSettings->numOfParticles;
            Colour lerpedCol = LerpBetweenColours(&simulatorSettings->lerpStartColour, &simulatorSettings->lerpEndColour, lerpPos);

            // Spawn a particle with lerped colour
            GenerateParticle(simulatorSettings->positionRange, simulatorSettings->velocityRange,
                                               simulatorSettings->sizeRange, simulatorSettings->massRange,
                                               simulatorSettings->elasticityRange,
                                               simulatorSettings->frictionRange,
                                               lerpedCol); // Generates Detailed Particles
            timeOfLastSpawn = time_;
        }else if (simulatorSettings->detailedParticles) {
            GenerateParticle(simulatorSettings->positionRange, simulatorSettings->velocityRange,
                                               simulatorSettings->sizeRange, simulatorSettings->massRange,
                                               simulatorSettings->elasticityRange,
                                               simulatorSettings->frictionRange); // Generates Detailed Particles
            timeOfLastSpawn = time_;
        } else {
            GenerateParticle(); // Generates regular particles
            timeOfLastSpawn = time_;
        }
    }
}

void ParticleGenerator::AddParticle(Particle particle) {

    particles.push_back(particle);
}

int ParticleGenerator::GetParticleCount() {

    return particles.size();
}

// Terrible attempt at Bounding Volume Hierarchies
/*void ParticleGenerator::UpdateParticleCollisionsBoundingVolumeHierarchies(){

    // Initialize an editable vector of particles
    std::map<Particle*, bool> particleMap; // Value represents if this particle has been added to
    for (Particle p : particles){
        particleMap[&p] = false;
    }

    // Find the distance between each particle
    std::map<std::pair<Particle*, Particle*>, float> particleDistances;
    for(int i = 0; i < particles.size(); i++){
        for(int j = i; j < particles.size(); j++){

            if(i != j){

                float distanceBetweenParticles = VectorDistance(particles[i].GetPosition(), particles[j].GetPosition());
                particleDistances[std::make_pair(&particles[i], &particles[j])] = distanceBetweenParticles;
            }
        }
    }

    // Sort the particle distance pairs by the distance
    std::vector<std::pair<Particle*, Particle*>> sortedDistancePairs = SortMapByValue(particleDistances);

    // Create Nodes of pairs starting from closest ensuring that each particle is only included once
    std::vector<BoundingBoxNode*> boundingBoxNodes;
    for (std::pair<Particle*, Particle*> pair : sortedDistancePairs){

        // Make sure the particles have not already been used for another node
        if(!particleMap[pair.first] && !particleMap[pair.second]){

            Particle* p1 = pair.first;
            Particle* p2 = pair.second;

            Vector2 pointBotLeft = Vector2();
            Vector2 pointTopRight = Vector2();

            // Get both particles sizes
            int p1Size = p1->GetSize();
            int p2Size = p2->GetSize();

            // Get both particles positions
            Vector2* p1Pos = p1->GetPosition();
            Vector2* p2Pos = p2->GetPosition();

            // Bounding Box Height Upper
            if(p1Pos->GetY() + p1Size >= p2Pos->GetY() + p2Size){

                pointTopRight.SetY(p1Pos->GetY() + p1Size);
            }else{

                pointTopRight.SetY(p2Pos->GetY() + p2Size);
            }

            // Bounding Box Height Lower
            if(p1Pos->GetY() - p1Size <= p2Pos->GetY() - p2Size){

                pointBotLeft.SetY(p1Pos->GetY() - p1Size);
            }else{

                pointBotLeft.SetY(p2Pos->GetY() - p2Size);
            }

            // Bounding Box Width Left
            if(p1Pos->GetX() - p1Size <= p2Pos->GetX() - p2Size){

                pointBotLeft.SetX(p1Pos->GetX() - p1Size);
            }else{

                pointBotLeft.SetX(p2Pos->GetX() - p2Size);
            }

            // Bounding Box Width Right
            if(p1Pos->GetX() + p1Size >= p2Pos->GetX() + p2Size){

                pointTopRight.SetX(p1Pos->GetX() + p1Size);
            }else{

                pointTopRight.SetX(p2Pos->GetX() + p2Size);
            }

            // Create a bounding box node for this particle pair
            Vector4 boundingBox = Vector4(pointBotLeft.GetX(), pointBotLeft.GetY(), pointTopRight.GetX(), pointTopRight.GetY());
            BoundingBoxNode boundingBoxNode = BoundingBoxNode(boundingBox);
            boundingBoxNodes.push_back(&boundingBoxNode);

            // Set particle map values to true so that these particles are not added to different nodes
            particleMap[p1] = true;
            particleMap[p2] = true;

            p1->SetColour(Colour(255,0,0,255));
            p2->SetColour(Colour(0,255,0,255));
        }
    }
}*/
