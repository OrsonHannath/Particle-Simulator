//
// Created by User on 3/03/2023.
//

#ifndef PARTICLESIMULATOR_MAPSORT_H
#define PARTICLESIMULATOR_MAPSORT_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

std::vector<std::pair<int, float>> SortMapByValue(std::map<int, float>& map);
bool ComparatorFunction(std::pair<int, float>& p1, std::pair<int, float>& p2);

#endif //PARTICLESIMULATOR_MAPSORT_H
