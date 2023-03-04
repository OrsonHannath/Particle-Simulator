//
// Created by User on 27/02/2023.
//

#ifndef PARTICLESIMULATOR_DELTATIME_H
#define PARTICLESIMULATOR_DELTATIME_H

#include <chrono>

// Returns current time
int CurrentTime();

// Calculates and Returns the difference in time between current time and stored time in seconds
float DeltaTime(int oldtTime);

#endif //PARTICLESIMULATOR_DELTATIME_H
