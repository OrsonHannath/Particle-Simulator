//
// Created by User on 5/03/2023.
//

#include "SDLText.h"

SDLText::SDLText(std::string string_, int fontSize, Colour colour, std::string &fontPath, SDL_Renderer* renderer_){

    textTexture = loadFont(string_, fontSize, colour, fontPath, renderer_);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void SDLText::Display(PositionOrigin posOrigin, int x, int y, SDL_Renderer* renderer_){

    switch (posOrigin) {
        case TopLeft:

            textRect.x = x;
            textRect.y = y;
            break;
        case TopRight:

            textRect.x = x - (textRect.w);
            textRect.y = y;
            break;
        case Center:

            textRect.x = x - (textRect.w/2);
            textRect.y = y - (textRect.h/2);
            break;
    }

    SDL_RenderCopy(renderer_, textTexture, nullptr, &textRect);
}

SDL_Texture* SDLText::loadFont(std::string string_, int fontSize, Colour colour, std::string &fontPath, SDL_Renderer* renderer_){

    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    if(!font){

        std::cerr << TTF_GetError() << std::endl;
    }

    auto textSurface_ = TTF_RenderText_Solid(font, string_.c_str(), colour.GetSDLColor());
    if (!textSurface_){

        std::cerr << "Failed to load text surface!" << std::endl;
    }

    auto textTexture_ = SDL_CreateTextureFromSurface(renderer_, textSurface_);
    if (!textTexture_){

        std::cerr << "Failed to load text texture!" << std::endl;
    }

    SDL_FreeSurface(textSurface_);
    return textTexture_;
}
