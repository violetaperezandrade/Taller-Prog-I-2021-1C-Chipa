#include "Controller.h"
#include <iostream>

Controller::Controller() {
    if(initSDL()) std::cerr << "Error al inicializar";
}
Controller::~Controller(){
    closeSDL();
}

bool Controller::initSDL() {

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Error video";
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::cerr << "Error al filtrar textura lineal";
    }
    return error;
}

bool Controller::closeSDL() {
    IMG_Quit();
    SDL_Quit();
}

/*int Controller::run(){

    bool quit = false;
    SDL_Event event;
    while (!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) quit = true;
                //key pressed
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        std::cout << "Arrow up pressed\n" ;
                        break;
                    case SDLK_DOWN:
                        std::cout << "Arrow down pressed\n";
                        break;
                    case SDLK_LEFT:
                        std::cout << "Arrow left pressed\n";
                        break;
                    case SDLK_RIGHT:
                        std::cout << "Arrow right pressed\n";
                        break;
                    default:
                        std::cout << "Some other key pressed\n";
                        break;
                }
            }
            else if(event.type == SDL_KEYUP && event.key.repeat == 0){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        std::cout << "Arrow up released\n" ;
                        break;
                    case SDLK_DOWN:
                        std::cout << "Arrow down released\n";
                        break;
                    case SDLK_LEFT:
                        std::cout << "Arrow left released\n";
                        break;
                    case SDLK_RIGHT:
                        std::cout << "Arrow right released\n";
                        break;
                    default:
                        std::cout << "Some other key released\n";
                        break;
                }
            }
        }
        SDL_Delay(30);
    }

    closeSDL();
    return 0;
}*/