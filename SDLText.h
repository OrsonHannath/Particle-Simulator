//
// Created by User on 5/03/2023.
//

#ifndef PARTICLESIMULATOR_SDLTEXT_H
#define PARTICLESIMULATOR_SDLTEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Framework.h"
#include "Colour.h"
#include "Enumerators.h"

class SDLText {

private:

    SDL_Texture* textTexture;
    SDL_Rect textRect;
public:

    SDLText(std::string string_, int fontSize, Colour colour, std::string &fontPath, SDL_Renderer* renderer_);

    void Display(PositionOrigin posOrigin, int x, int y, SDL_Renderer* renderer_);

    SDL_Texture* loadFont(std::string string_, int fontSize, Colour colour, std::string &fontPath, SDL_Renderer* renderer_);
};


#endif //PARTICLESIMULATOR_SDLTEXT_H
