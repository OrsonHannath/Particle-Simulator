//
// Created by User on 28/02/2023.
//

#ifndef PARTICLESIMULATOR_VECTOR4_H
#define PARTICLESIMULATOR_VECTOR4_H


class Vector4 {
private:
    float x;
    float y;
    float z;
    float w;
public:
    Vector4(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_){};
    Vector4() : x(0), y(0), z(0), w(0){};

    void SetPosition(float x_, float y_, float z_, float w_);
    void SetX(float x_);
    void SetY(float y_);
    void SetZ(float z_);
    void SetW(float w_);

    float GetX();
    float GetY();
    float GetZ();
    float GetW();
};


#endif //PARTICLESIMULATOR_VECTOR4_H
