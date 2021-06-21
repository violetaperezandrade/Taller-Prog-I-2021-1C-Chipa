#ifndef DONKEYKONG_TEXT_H
#define DONKEYKONG_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>


class Text {

private:
    SDL_Texture* textTexture = nullptr;
    SDL_Rect textRect;
public:
    Text(SDL_Renderer* renderer, const std::string &fontPath, int fontSize, const std::string &msg, SDL_Color color);

    void display(int x, int y, SDL_Renderer* renderer);

    SDL_Texture* loadFont(SDL_Renderer* renderer, const std::string &fontPath, int fontSize,
                          const std::string &msg, SDL_Color color);

};


#endif //DONKEYKONG_TEXT_H
