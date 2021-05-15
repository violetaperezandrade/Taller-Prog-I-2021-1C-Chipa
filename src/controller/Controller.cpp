#include "Controller.h"
#include <iostream>
Config config;

Controller::Controller(): game(&config), view(){
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

int Controller::run(){

    bool quit = false;
    View vista;
    SDL_Event event;
    while (!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) quit = true;
                //key pressed
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        game.moveCharacterUp();
                        break;
                    case SDLK_DOWN:
                        game.moveCharacterDown();
                        break;
                    case SDLK_LEFT:
                        game.moveCharacterLeft();
                        break;
                    case SDLK_RIGHT:
                        game.moveCharacterRight();
                        break;
                    case SDLK_l:
                        game.changeLevel();
                        break;
                    default:
                        break;
                }
            }
            else if(event.type == SDL_KEYUP && event.key.repeat == 0){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        game.stopMovingUp();
                        break;
                    case SDLK_DOWN:
                        game.stopMovingDown();
                        break;
                    case SDLK_LEFT:
                        game.stopMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        game.stopMovingRight();
                        break;
                    default:
                        break;
                }
            }
            Message entityInfo = game.get_status();
            while(!entityInfo.isEmpty()){
                char entityType;
                int posX;
                int posY;
                int width;
                int height;
                char state;
                entityInfo.getEntityInfo(entityType,posX,posY,width,height,state);
                vista.render(posX,posY,width,height,state,entityType);
            }
        }
        game.update();
        vista.refresh();
    }
    closeSDL();
    return 0;
}