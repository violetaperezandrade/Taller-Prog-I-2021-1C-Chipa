#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <map>
#include "../server/ScreenConfig.h"
#include "../server/Game.h"
#include "../common/Logger.h"
#include "../server/Config.h"

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
    SDL_Texture* defaultConfig;

    bool initSDL();
    void closeSDL();
public:
    //void render(int x, int y, int width, int height, SDL_Texture* texture, SDL_Renderer* windowRenderer);
    void render(int x, int y, int width, int height, char stateEntity,char entityType);

    SDL_Renderer* createRenderer(SDL_Window* window);

    SDL_Window* createWindow(const char* title);

    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);

    void free(SDL_Texture* texture);
    //int run();
    View(Game& game, Logger& logger, Config& config);

    void changeLevel();

    ~View();

    void refresh();

    void renderFilledQuad();

};

#endif //VIEW_H
