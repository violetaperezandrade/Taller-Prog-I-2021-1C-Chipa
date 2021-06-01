#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <iostream>
#include "../server/Game.h"
#include "../client/View.h"
#include "Config.h"
#include "Logger.h"

class Controller {
private:
    Config& config;
    Game game;
    View view;
    Logger& logger;
public:
    Controller(Config& config, Logger& logger);
    ~Controller();
    int run();
    bool initSDL();
    void closeSDL();
};


#endif //CONTROLLER_H
