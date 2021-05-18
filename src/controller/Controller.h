#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <iostream>
#include "../model/Game.h"
#include "../view/View.h"
#include "Config.h"
#include "Logger.h"

class Controller {
private:
    Game game;
    View view;
    Logger& logger;
public:
    //Controller(Config& config);
    explicit Controller(Logger& logger);
    ~Controller();
    int run();
    bool initSDL();
    void closeSDL();
};


#endif //CONTROLLER_H
