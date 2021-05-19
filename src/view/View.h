#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "../model/ScreenConfig.h"
#include "../model/Game.h"
#include "../controller/Logger.h"
#include "../controller/Config.h"

class View {
private:
    std::map<char, SDL_Texture*> texturesMario; //only mario
    std::map<char, SDL_Texture*> texturesEntities; //entities - mario - monkey
    std::map<char, SDL_Texture*> texturesMonkey; //only monkey
    SDL_Renderer* windowRenderer;
    SDL_Window* window;
    Game& game;
    Logger& logger;
    Config& config;
public:
    //void render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer);
    void render(int x, int y, int width, int height, char stateEntity,char entityType);

    SDL_Renderer* createRenderer(SDL_Window* window);

    SDL_Window* createWindow(const char* title);

    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);

    void free(SDL_Texture* texture);
    //int run();
    explicit View(Game& game, Logger& logger, Config& config);

    void refresh();

    void renderFilledQuad();

};

#endif //VIEW_H
