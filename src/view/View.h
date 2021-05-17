#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "../model/ScreenConfig.h"

class View {
public:
    //void render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer);
    void render(int x, int y, int width, int height, char stateEntity,char entityType);
    SDL_Renderer* createRenderer(SDL_Window* window);
    SDL_Window* createWindow(const char* title);
    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);
    void free(SDL_Texture* texture);
    //int run();
    View();
    void refresh();
    void renderFilledQuad();

private:
    std::map<char, std::string> texturesMario; //only mario
    std::map<char, std::string> texturesEntities; //entities - mario - monkey
    std::map<char, std::string> texturesMonkey; //only monkey
    SDL_Renderer* windowRenderer;
    SDL_Window* window;
};

#endif //VIEW_H
