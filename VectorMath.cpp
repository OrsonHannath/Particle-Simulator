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

float VectorDistance(Vector2 vec1, Vector2 vec2){

    //std::cout << pow((vec1.GetX() - vec2.GetX()), 2) << std::endl;
    return sqrt((pow((vec1.GetX() - vec2.GetX()), 2)) + (pow((vec1.GetY() - vec2.GetY()), 2))); // a*a + b*b = c*c trigonometry
}


float VectorDistance(Vector2* vec1, Vector2* vec2){

    //std::cout << pow((vec1.GetX() - vec2.GetX()), 2) << std::endl;
    return sqrt((pow((vec1->GetX() - vec2->GetX()), 2)) + (pow((vec1->GetY() - vec2->GetY()), 2))); // a*a + b*b = c*c trigonometry
}

double VectorMagnitude(Vector2 vec) {

    return std::sqrt(vec.GetX() * vec.GetX() + vec.GetY() * vec.GetY());
}

Vector2 VectorUnit(Vector2 vec) {

    double mag = VectorMagnitude(vec);

    if (mag != 0.) {

        return Vector2(vec.GetX() / mag, vec.GetY() / mag);
    } else {

        return Vector2();
    }
}

float VectorDotProduct(Vector2 vec1, Vector2 vec2) {

    return (vec1.GetX() * vec2.GetX() + vec1.GetY() * vec2.GetY());
}