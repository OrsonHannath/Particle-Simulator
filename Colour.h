//
// Created by User on 26/02/2023.
//

#ifndef PARTICLESIMULATOR_COLOUR_H
#define PARTICLESIMULATOR_COLOUR_H


class Colour {
private:
    float red;
    float green;
    float blue;
    float alpha;
public:
    Colour(float red_, float green_, float blue_, float alpha_) : red(red_), green(green_), blue(blue_), alpha(alpha_){};

    void SetRed(float red_);
    void SetGreen(float green_);
    void SetBlue(float blue_);
    void SetAlpha(float alpha_);

    float GetRed();
    float GetGreen();
    float GetBlue();
    float GetAlpha();

};


#endif //PARTICLESIMULATOR_COLOUR_H
