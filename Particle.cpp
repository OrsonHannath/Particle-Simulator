//
// Created by User on 27/02/2023.
//

#include "Particle.h"
#include "VectorMath.h"

void Particle::BoundaryCollisions(Framework* fw){

    // Detect Left Boundary Collision
    if (position.GetX() - (size/2) <= -(fw->GetWidth()/2) && velocity.GetX() < 0){

        velocity.SetX(-velocity.GetX()); // Invert X if Collision
    }

    // Detect Right Boundary Collision
    if (position.GetX() + (size/2) >= (fw->GetWidth()/2) && velocity.GetX() > 0){

        velocity.SetX(-velocity.GetX()); // Invert X if Collision
    }

    // Detect Top Boundary Collision
    if (position.GetY() + (size/2) >= (fw->GetHeight()/2) && velocity.GetY() > 0){

        velocity.SetY(-velocity.GetY()); // Invert Y if Collision
    }

    // Detect Bottom Boundary Collision
    if (position.GetY() - (size/2) <= -(fw->GetHeight()/2) && velocity.GetY() < 0){

        velocity.SetY(-velocity.GetY()); // Invert Y if Collision
    }
}

void Particle::UpdateParticle(Framework* fw, float deltaTime){

    // Update the position of the particle
    velocity = VectorAddition(velocity, VectorMultiply(acceleration, deltaTime)); // Update Velocity
    position = VectorAddition(position, VectorMultiply(velocity, deltaTime)); // Update Position

    // Detect Boundary Collision
    BoundaryCollisions(fw);

    // Update the particle graphics
    fw->DrawCircle(position.GetX(), position.GetY(), size, colour);
}

// This checks if two particles are colliding and then adjusts their velocities
void Particle::ParticleCollision(Particle *collisionP) {

    // Check if the particles are colliding
    if(VectorDistance(position, collisionP->position) <= (size/2) + (collisionP->size/2)){

        // Ensure particles have mass otherwise return
        if (mass == 0. && collisionP->mass == 0.){
            return;
        }

        // Determine the Normal Vector of Collision
        Vector2 normalVec = VectorSubtraction(collisionP->position, position); // Normal Vector of Collision
        Vector2 unitNormalVec = VectorUnit(normalVec); // Unit Normal Vector of Collision
        Vector2 unitTangentVec = Vector2(-unitNormalVec.GetY(), unitNormalVec.GetX()); // Unit Tangent Vector of Collision

        // Scalar Projections
        float v1Normal = VectorDotProduct(unitNormalVec, velocity);
        float v2Normal = VectorDotProduct(unitNormalVec, collisionP->velocity);
        float v1Tangent = VectorDotProduct(unitTangentVec, velocity);
        float v2Tangent = VectorDotProduct(unitTangentVec, collisionP->velocity);

        // Calculate New Velocities
        float v1NormalScalar = (v1Normal * (mass - collisionP->mass) + 2.0 * collisionP->mass * v2Normal) / (mass + collisionP->mass);
        float v2NormalScalar = (v2Normal * (collisionP->mass - mass) + 2.0 * mass * v1Normal) / (mass+ collisionP->mass);

        // Determine New Normal and Tangent Velocity Vectors
        Vector2 thisVelNormal = VectorMultiply(unitNormalVec, v1NormalScalar);
        Vector2 collisionVelNormal = VectorMultiply(unitNormalVec, v2NormalScalar);
        Vector2 thisVelTangent = VectorMultiply(unitTangentVec, v1Tangent);
        Vector2 collisionVelTangent = VectorMultiply(unitTangentVec, v2Tangent);

        // Update the Particle Velocities
        this->SetVelocity(VectorAddition(thisVelNormal, thisVelTangent));
        collisionP->SetVelocity(VectorAddition(collisionVelNormal, collisionVelTangent));

        //std::cout << "collision" << std::endl;
    }
}

void Particle::SetPosition(Vector2 position_){

    position = position_;
}

void Particle::SetVelocity(Vector2 velocity_){

    velocity = velocity_;
}

void Particle::SetAcceleration(Vector2 acceleration_){

    acceleration = acceleration_;
}

Vector2* Particle::GetPosition(){

    return &position;
}

Vector2* Particle::GetVelocity(){

    return &velocity;
}

Vector2* Particle::GetAcceleration(){

    return &acceleration;
}