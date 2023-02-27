//
// Created by User on 27/02/2023.
//

#ifndef PARTICLESIMULATOR_DELTATIME_H
#define PARTICLESIMULATOR_DELTATIME_H

#include <chrono>

// Returns current time
int CurrentTime(){

    return (int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// Calculates and Returns the difference in time between current time and stored time in seconds
float DeltaTime(int oldtTime){

    return ((CurrentTime() - oldtTime) / 1000.0);
}

#endif //PARTICLESIMULATOR_DELTATIME_H
