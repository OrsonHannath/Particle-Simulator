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
    Colour colour = Colour(255, 0, 255, 255);
    int size = 10;
    int weight = 10;
public:
    Particle(Vector2 position_, Vector2 velocity_, Vector2 acceleration_) : position(position_), velocity(velocity_),
                                                                            acceleration(acceleration_),
                                                                            colour(RandomColour()){};

    Particle(Vector2 position_, Vector2 velocity_) : position(position_), velocity(velocity_),
                                                                          acceleration(Vector2(0, 0)),
                                                                          colour(RandomColour()){};

    Particle(Vector2 position_, int size_, int weight_) : position(position_), size(size_), weight(weight_),
                                                          velocity(Vector2(0, 0)), acceleration(Vector2(0,0)),
                                                          colour(RandomColour()){};

    Particle(Vector2 position_, int size_) :  position(position_), size(size_), velocity(Vector2(0, 0)), acceleration(Vector2(0,0)),
                                              colour(RandomColour()){};

    Particle(Vector2 position_) :  position(position_), velocity(Vector2(0, 0)), acceleration(Vector2(0,0)),
                                   colour(RandomColour()){};

    void UpdateParticle(Framework* fw, float deltaTime);
    void BoundaryCollisions(Framework* fw);

    void SetPosition(Vector2 position_);
    void SetVelocity(Vector2 velocity_);
    void SetAcceleration(Vector2 acceleration_);

    Vector2* GetPosition();
    Vector2* GetVelocity();
    Vector2* GetAcceleration();
};


#endif //PARTICLESIMULATOR_PARTICLE_H
