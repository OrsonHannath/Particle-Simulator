//
// Created by User on 27/02/2023.
//

#include "Particle.h"
#include "VectorMath.h"

void Particle::BoundaryCollisions(Framework* fw){

    // Detect Left Boundary Collision
    if (position.GetX() - (size/2) <= 0 && velocity.GetX() < 0){

        velocity.SetX(-velocity.GetX()); // Invert X if Collision
    }

    // Detect Right Boundary Collision
    if (position.GetX() + (size/2) >= fw->GetWidth() && velocity.GetX() > 0){

        velocity.SetX(-velocity.GetX()); // Invert X if Collision
    }

    // Detect Top Boundary Collision
    if (position.GetY() - (size/2) <= 0 && velocity.GetY() < 0){

        velocity.SetY(-velocity.GetY()); // Invert Y if Collision
    }

    // Detect Bottom Boundary Collision
    if (position.GetY() + (size/2) >= fw->GetHeight() && velocity.GetY() > 0){

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