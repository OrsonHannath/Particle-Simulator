//
// Created by User on 3/03/2023.
//

#include "MapSort.h"

std::vector<std::pair<int, float>> SortMapByValue(std::map<int, float>& map){

    // Declare vector of pairs
    std::vector<std::pair<int, float> > pairsVec;

    // Copy key-value pair from Map to vector of pairs
    for (auto& it : map) {

        pairsVec.push_back(it);
    }

    // Sort using comparator function
    sort(pairsVec.begin(), pairsVec.end(), ComparatorFunctionIntFloat);

    // Return the sorted map as a pair vector
    return pairsVec;
}

bool ComparatorFunctionIntFloat(std::pair<int, float>& p1, std::pair<int, float>& p2){

    return p1.second < p2.second;
}

std::vector<std::pair<Particle*, Particle*>> SortMapByValue(std::map<std::pair<Particle*, Particle*>, float>& map){

    // Declare vector of pairs
    std::vector<std::pair<std::pair<Particle*, Particle*>, float>> pairsVec;

    // Copy key-value pair from Map to vector of pairs
    for (auto& it : map) {

        pairsVec.push_back(it);
    }

    // Sort using comparator function
    sort(pairsVec.begin(), pairsVec.end(), ComparatorFunctionParticlePairFloat);

    std::vector<std::pair<Particle*, Particle*>> returnVec;
    for(auto& particlePair : pairsVec){
        returnVec.push_back(particlePair.first);
    }

    // Return the sorted map as a pair vector
    return returnVec;
}

bool ComparatorFunctionParticlePairFloat(std::pair<std::pair<Particle*, Particle*>, float>& p1, std::pair<std::pair<Particle*, Particle*>, float>& p2){

    return p1.second < p2.second;
}