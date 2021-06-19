#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
#include "../server/Game.h"
#include "../common/Logger.h"
#include "../common/Config.h"
#include "../client/Monitor.h"
#include <condition_variable>

class View {
private:
    std::map<int, std::map<char, SDL_Texture*>> texturesMario; //only mario
    std::map<char, SDL_Texture*> texturesEntities; //entities - mario - monkey
    std::map<char, SDL_Texture*> texturesMonkey; //only monkey
    SDL_Renderer* windowRenderer;
    SDL_Window* window;
    //Game& game;
    Logger& logger;
    Config& config;
    SDL_Texture* defaultConfig;
    Monitor& monitor;
    std::condition_variable condVar;
    int playerID;
    bool initSDL();
    void closeSDL();
    bool keepRuning;
public:

    void render(int x, int y, int width, int height, char stateEntity,char entityType);

    SDL_Renderer* createRenderer(SDL_Window* window);

    SDL_Window* createWindow(const char* title,int width, int height);

    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);

    void free(SDL_Texture* texture);

    View(Monitor& monitor, Logger& logger, Config& config);

    void changeLevel();

    ~View();

    void refresh();

    void renderFilledQuad();

    int run();

    SDL_Window* getWindow();

};

#endif //VIEW_H
