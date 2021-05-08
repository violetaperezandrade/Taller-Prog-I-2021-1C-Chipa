#ifndef VIEW_H
#define VIEW_H
#include "../controller/Controller.h"

class View {
public:
    void render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer);
    SDL_Renderer* createRenderer(SDL_Window* window);
    SDL_Window* createWindow(const char* title);
    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);
    void free(SDL_Texture* texture);
    int run();
};


#endif //VIEW_H
