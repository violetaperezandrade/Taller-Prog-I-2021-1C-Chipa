#ifndef VIEW_H
#define VIEW_H
#define FONTSIZE 24
/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>*/
#include <map>
#include "../server/Game.h"
#include "../common/Logger.h"
#include "../common/Config.h"
#include "../client/Monitor.h"
#include "../client/Login.h"
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
    SDL_Texture* defaultConfig;
    Monitor& monitor;
    std::condition_variable condVar;
    TTF_Font* font;
    int playerID;
    bool& keepRuning;
    bool initSDL();
    void closeSDL();

public:
    void render(int x, int y, int width, int height, char stateEntity,char entityType);

    SDL_Renderer* createRenderer(SDL_Window* window);

    SDL_Window* createWindow(const char* title,int width, int height);

    SDL_Texture* loadImageTexture(std::string path, SDL_Renderer* renderer);

    TextRendered loadFromRenderedText(std::string textureText,SDL_Color textColor,SDL_Renderer* renderer, TTF_Font* font);

    void renderText(int x, int y, int width, int height, SDL_Texture* texture);

    void free(SDL_Texture* texture);

    View(Monitor& monitor, Logger& logger, Config& config, bool& keepRunning);

    void changeLevel();

    ~View();

    void renderFilledQuad();

    int run();
};

#endif //VIEW_H
