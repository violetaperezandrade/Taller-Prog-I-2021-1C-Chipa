#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include <iostream>
#include "../model/Game.h"
#include "../view/View.h"
#include "Config.h"

class Controller {
private:
    Game game;
    View view;
public:
    //Controller(Config& config);
    Controller();
    ~Controller();
    int run();
    bool initSDL();
    void closeSDL();
};


#endif //CONTROLLER_H
