#ifndef DONKEYKONG_SDLMANAGER_H
#define DONKEYKONG_SDLMANAGER_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../common/Logger.h"
#include <vector>

struct TextRendered{
    SDL_Texture* texture;
    int width;
    int height;
};

class SDLManager {
private:
    Logger& logger;
    bool initSDL();
    bool closeSDL();

public:
    SDLManager(Logger& logger);
    SDL_Renderer* createRenderer(SDL_Window* window);
    SDL_Window* createWindow(const char* title,int width, int height);
    TTF_Font* createFont(std::string path, int size);
    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);
    TextRendered loadFromRenderedText(std::string textureText, SDL_Color textColor,
                                      SDL_Renderer* renderer, TTF_Font* font);

    void render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* renderer,
                SDL_Rect* clip = NULL);
    void renderWarnings(std::string message, SDL_Renderer* renderer,SDL_Window* window);
    bool mouseWasClickedOnPosition(int x1, int x2, int y1, int y2, SDL_Event* e);
    void renderFilledQuad(SDL_Renderer* renderer,int width, int height);

    void destroyTexture(SDL_Texture* texture);
    void freeAllTextures(std::vector<SDL_Texture*>& vector);
    void destroyFont(TTF_Font* font);
    void destroyWindow(SDL_Window* window);
    void destroyRenderer(SDL_Renderer* renderer);

    void clearRender(SDL_Renderer* renderer);
    void presentRender(SDL_Renderer* renderer);
    void startInputText();
    void finishInputText();
    ~SDLManager();
};


#endif //DONKEYKONG_SDLMANAGER_H
