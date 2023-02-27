//
// Created by User on 27/02/2023.
//

#include "VectorMath.h"

Vector2 VectorMultiply(Vector2 vec, float scalar){

    return {vec.GetX() * scalar, vec.GetY() * scalar};
}

Vector2 VectorDivide(Vector2 vec, float scalar){

    return {vec.GetX() / scalar, vec.GetY() / scalar};
}

Vector2 VectorAddition(Vector2 vec1, Vector2 vec2){

    return {vec1.GetX() + vec2.GetX(), vec1.GetY() + vec2.GetY()};
}

Vector2 VectorSubtraction(Vector2 vec1, Vector2 vec2){

    return {vec1.GetX() - vec2.GetX(), vec1.GetY() - vec2.GetY()};
}

