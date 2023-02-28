//
// Created by User on 28/02/2023.
//

#include "Vector4.h"

void Vector4::SetPosition(float x_, float y_, float z_, float w_){

    x = x_;
    y = y_;
    z = z_;
    w = w_;
}

void Vector4::SetX(float x_){

    x = x_;
}

void Vector4::SetY(float y_){

    y = y_;
}

void Vector4::SetZ(float z_){

    z = z_;
}

void Vector4::SetW(float w_){

    w = w_;
}

float Vector4::GetX(){

    return x;
}

float Vector4::GetY(){

    return y;
}

float Vector4::GetZ(){

    return z;
}

float Vector4::GetW(){

    return w;
}