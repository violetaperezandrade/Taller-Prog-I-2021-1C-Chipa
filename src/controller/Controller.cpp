#include "Controller.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

Controller::Controller() : window(NULL){
    initSDL();
}
Controller::~Controller(){
    closeSDL();
}

bool Controller::initSDL() {

    bool error = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cerr << "Error video";
        error = true;
    }
    else{
        window = SDL_CreateWindow("Prueba donkey kong",
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH,
                                  SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
        if(!window){
            std::cerr << "Error window";
            error = true;
        }
    }
    return error;
}

bool Controller::closeSDL() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int Controller::run(){

    if(initSDL()) std::cerr << "Error al inicializar";
    else{
        bool quit = false;
        SDL_Event event;
        while (!quit){
            while(SDL_PollEvent(&event) != 0){
                if(event.type == SDL_QUIT) quit = true;
                //key pressed
                else if(event.type == SDL_KEYDOWN){
                    switch(event.key.keysym.sym){
                        case SDLK_UP:
                            std::cout << "Arrow up pressed";
                            break;
                        case SDLK_DOWN:
                            printf("Arrow down pressed");
                            break;
                        case SDLK_LEFT:
                            printf("Arrow left pressed");
                            break;
                        case SDLK_RIGHT:
                            printf("Arrow right pressed");
                            break;
                        default:
                            printf("Some other key pressed");
                    }
                }
            }
        }
    }
    closeSDL();
    return 0;
}