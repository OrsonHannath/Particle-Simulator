//
// Created by User on 27/02/2023.
//

#ifndef PARTICLESIMULATOR_PARTICLE_H
#define PARTICLESIMULATOR_PARTICLE_H

#include "Vector2.h"
#include "Framework.h"
#include "ColourRandomizer.h"

class Particle {
private:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    Vector2* gravity;
    Colour colour = Colour(255, 0, 255, 255);
    Colour collisionColour = Colour(255, 0, 255, 255);
    int size = 100;
    int mass = 10;
    float elasticity = 0.5; // 0 Means no Bounce, 1 Means full Bounce
    float friction = 0.2; // 0 Means full Friction, 1 Means no Friction
    bool collided = false;
    Particle* collidedParticle = nullptr;
public:
    Particle(Vector2 position_, Vector2* gravity_) : position(position_), velocity(Vector2(0, 0)),
                                                     acceleration(Vector2(0,0)), colour(RandomColour()), gravity(gravity_){};

    Particle(Vector2 position_, Vector2 velocity_, int size_, int mass_, float elasticity_, float friction_,
                                Vector2* gravity_) : position(position_), velocity(velocity_), size(size_),
                                mass(mass_), elasticity(elasticity_), friction(friction_), gravity(gravity_), colour(RandomColour()){};

    Particle(Vector2 position_, Vector2 velocity_, Vector2 acceleration_, Vector2* gravity_) : position(position_), velocity(velocity_),
                                                                            acceleration(acceleration_),
                                                                            colour(RandomColour()), gravity(gravity_){};

    Particle(Vector2 position_, Vector2 velocity_, Vector2* gravity_) : position(position_), velocity(velocity_),
                                                                          acceleration(Vector2(0, 0)),
                                                                          colour(RandomColour()), gravity(gravity_){};

    Particle(Vector2 position_, int size_, int mass_, Vector2* gravity_) : position(position_), size(size_), mass(mass_),
                                                          velocity(Vector2(0, 0)), acceleration(Vector2(0,0)),
                                                          colour(RandomColour()), gravity(gravity_){};

    Particle(Vector2 position_, int size_, int mass_, Vector2 velocity_, Vector2* gravity_) : position(position_), size(size_), mass(mass_),
                                                          velocity(velocity_), acceleration(Vector2(0,0)),
                                                          colour(RandomColour()), gravity(gravity_){};

    Particle(Vector2 position_, int size_, Vector2* gravity_) :  position(position_), size(size_), velocity(Vector2(0, 0)), acceleration(Vector2(0,0)),
                                              colour(RandomColour()), gravity(gravity_){};

    void UpdateParticle(Framework* fw, float deltaTime);
    void BoundaryCollisions(Framework* fw);
    bool ParticleCollision(Particle* collisionP);

    void SetPosition(Vector2 position_);
    void SetVelocity(Vector2 velocity_);
    void SetAcceleration(Vector2 acceleration_);
    void SetCollided(bool collided_);

    float CalculateBounceCoefficient();

    Vector2* GetPosition();
    Vector2* GetVelocity();
    Vector2* GetAcceleration();
    Particle* GetCollidedParticle();
};


#endif //PARTICLESIMULATOR_PARTICLE_H
