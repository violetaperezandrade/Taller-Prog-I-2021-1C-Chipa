#ifndef VIEW_H
#define VIEW_H
#define FONTSIZE 24
#define FONTSIZE_IDENTIFIERS 10

#include <map>
#include "../server/Game.h"
#include "../common/Logger.h"
#include "../common/Config.h"
#include "../client/Monitor.h"
#include "SDLManager.h"
#include <condition_variable>


class View {
private:
    std::map<int, std::map<char, SDL_Texture*>> texturesMario; //only mario
    std::map<char, SDL_Texture*> texturesEntities; //entities - mario - monkey
    std::map<char, SDL_Texture*> texturesMonkey; //only monkey
    std::map<int, TextRendered> usersNames;
    SDL_Renderer* windowRenderer;
    SDL_Window* window;
    Logger& logger;
    Config& config;
    SDLManager& sdlMngr;
    SDL_Texture* defaultConfig;
    Monitor& monitor;
    std::condition_variable condVar;
    TTF_Font* font;
    int playerID;
    bool& keepRuning;
    bool& serverActive;

public:
    View(Monitor& monitor, Logger& logger, Config& config,SDLManager& mngr, bool& keepRunning, bool& serverActive);

    void changeLevel();

    ~View();

    int run();

    void getEntityInfoAndRender(int x, int y, int width, int height, char stateEntity,char entityType);
};

#endif //VIEW_H
