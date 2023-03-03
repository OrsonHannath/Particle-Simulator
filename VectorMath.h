//
// Created by User on 27/02/2023.
//

#ifndef PARTICLESIMULATOR_VECTORMATH_H
#define PARTICLESIMULATOR_VECTORMATH_H

#include "Vector2.h"
#include <cmath>
#include <iostream>

Vector2 VectorMultiply(Vector2 vec, float scalar);
Vector2 VectorDivide(Vector2 vec, float scalar);
Vector2 VectorAddition(Vector2 vec1, Vector2 vec2);
Vector2 VectorSubtraction(Vector2 vec1, Vector2 vec2);

float VectorDistance(Vector2 vec1, Vector2 vec2);
float VectorDistance(Vector2* vec1, Vector2* vec2);
float VectorDotProduct(Vector2 vec1, Vector2 vec2);
Vector2 VectorUnit(Vector2 vec);
double VectorMagnitude(Vector2 vec);

#endif //PARTICLESIMULATOR_VECTORMATH_H
