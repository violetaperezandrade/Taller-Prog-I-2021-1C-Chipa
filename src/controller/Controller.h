#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <string>
#include "../model/Entity.h"
#include <iostream>
#include "../model/Game.h"
#include "../view/View.h"

class Controller {
private:
    Game game;
    View view;
public:
    Controller();
    ~Controller();
    //int run();
    bool initSDL();
    bool closeSDL();
};


#endif //CONTROLLER_H
