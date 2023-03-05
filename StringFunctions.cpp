//
// Created by User on 5/03/2023.
//

#include "StringFunctions.h"

std::string FloatToString(float f, int precision){

    std::ostringstream out;
    out.precision(precision);
    out << std::fixed << f;
    return out.str();
}
