#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "SDL2/SDL.h"

class Controller {
private:
    SDL_Window* window;

public:
    Controller();
    ~Controller();
    int run();
    bool initSDL();
    bool closeSDL();
};


#endif //CONTROLLER_H
