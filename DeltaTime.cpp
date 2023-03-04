//
// Created by User on 4/03/2023.
//

#include "DeltaTime.h"

// Returns current time
int CurrentTime(){

    return (int)std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// Calculates and Returns the difference in time between current time and stored time in seconds
float DeltaTime(int oldtTime){

    return ((CurrentTime() - oldtTime) / 1000.0);
}
