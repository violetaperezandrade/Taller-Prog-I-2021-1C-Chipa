#ifndef VIEW_H
#define VIEW_H
#define FONTSIZE_RESULTS 24
#define FONTSIZE_POINTS_FINAL 20
#define FONTSIZE_IDENTIFIERS 13
#define ROLLING_BARREL_FRAMES 4


#include <map>
#include <iomanip>
#include <sstream>
#include "../server/Game.h"
#include "../common/Logger.h"
#include "../common/Config.h"
#include "../client/Monitor.h"
#include "SDLManager.h"
#include "SoundManager.h"


class View {
private:
    std::map<int, std::map<char, SDL_Texture*>> texturesMario; //only mario
    std::map<char, SDL_Texture*> texturesEntities; //entities - mario - monkey
    std::map<char, SDL_Texture*> texturesMonkey; //only monkey
    std::map<int, TextRendered> usersNames;
    std::map<int,SDL_Color> playersColor;
    SDL_Renderer* windowRenderer;
    SDL_Window* window;
    Logger& logger;
    Config& config;
    SDLManager& sdlMngr;
    SDL_Texture* defaultConfig;
    SDL_Texture* divisorPoints;
    Monitor& monitor;
    TTF_Font* font;
    SoundManager& soundManager;
    int playerID;
    bool& keepRuning;
    bool& serverActive;
    int& playerNumber;
    int points[4];
    int lives[4];
    int& playerAmount;
    int& endGame;
    int hammerState[4];

    //For barrel animation
    int frame = 0;
    SDL_Rect spriteFrames[ROLLING_BARREL_FRAMES];
    SDL_Texture* spriteSheet;

public:
    View(Monitor& monitor, Logger& logger, Config& config,SDLManager& mngr, bool& keepRunning, bool& serverActive,
         int& playerNumber, SoundManager& soundManager, int& playerAmount, int& endGame);

    void changeLevel();

    int run();

    void getEntityInfoAndRender(int x, int y, int width, int height, char stateEntity,char entityType);

    void renderPlayerID(int posX, int width, int posY);

    void renderEntity(std::vector<Entity>::iterator it, std::vector<char>& states);

    void renderLivesAndPoints();

    void renderPartialResults();

    void renderFinalResults(int* pointsLvl1);

    void renderBarrelAnimation(int x, int y, int width, int height);

    ~View();
};

#endif //VIEW_H
