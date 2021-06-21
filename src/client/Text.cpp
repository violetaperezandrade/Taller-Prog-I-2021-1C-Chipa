#include "Text.h"
#include <iostream>

Text::Text(SDL_Renderer* renderer, const std::string &fontPath, int fontSize, const std::string &msg, SDL_Color color){
    textTexture = loadFont(renderer, fontPath, fontSize, msg, color);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::display(int x, int y, SDL_Renderer* renderer){
    textRect.x = x;
    textRect.y = y;
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
}

SDL_Texture* Text::loadFont(SDL_Renderer* renderer, const std::string &fontPath, int fontSize, const std::string &msg, SDL_Color color){
    TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);
    //if (!font){}
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, msg.c_str(), color);
    //if(!textSurface){}
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    //if(!textTexture)
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
    return texture;
}

