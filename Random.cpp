//
// Created by User on 27/02/2023.
//

#include "Random.h"

int RandomNumber(int startRange, int endRange){

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(startRange, endRange);

    return dis(gen);
}
