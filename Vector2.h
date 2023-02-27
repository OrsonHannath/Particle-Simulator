//
// Created by User on 27/02/2023.
//

#ifndef PARTICLESIMULATOR_VECTOR2_H
#define PARTICLESIMULATOR_VECTOR2_H


class Vector2 {
private:
    float x;
    float y;
public:
    Vector2(float x_, float y_) : x(x_), y(y_){};

    void SetPosition(float x_, float y_);
    void SetX(float x_);
    void SetY(float y_);

    float GetX();
    float GetY();
};


#endif //PARTICLESIMULATOR_VECTOR2_H
