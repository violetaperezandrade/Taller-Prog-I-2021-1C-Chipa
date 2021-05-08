#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <string>
#include "../model/Entity.h"
#include <iostream>

class Controller {
private:
public:
    Controller();
    ~Controller();
    //int run();
    bool initSDL();
    bool closeSDL();
};


#endif //CONTROLLER_H
