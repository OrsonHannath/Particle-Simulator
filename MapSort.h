//
// Created by User on 3/03/2023.
//

#ifndef PARTICLESIMULATOR_MAPSORT_H
#define PARTICLESIMULATOR_MAPSORT_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include "Particle.h"

std::vector<std::pair<int, float>> SortMapByValue(std::map<int, float>& map);
bool ComparatorFunctionIntFloat(std::pair<int, float>& p1, std::pair<int, float>& p2);

std::vector<std::pair<Particle*, Particle*>> SortMapByValue(std::map<std::pair<Particle*, Particle*>, float>& map);
bool ComparatorFunctionParticlePairFloat(std::pair<std::pair<Particle*, Particle*>, float>& p1, std::pair<std::pair<Particle*, Particle*>, float>& p2);

#endif //PARTICLESIMULATOR_MAPSORT_H
