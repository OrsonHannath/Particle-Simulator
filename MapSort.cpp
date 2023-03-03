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
    sort(pairsVec.begin(), pairsVec.end(), ComparatorFunction);

    // Return the sorted map as a pair vector
    return pairsVec;
}

bool ComparatorFunction(std::pair<int, float>& p1, std::pair<int, float>& p2){

    return p1.second < p2.second;
}