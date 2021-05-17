#include "Controller.h"
#include <iostream>

Controller::Controller():game(), view(){
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

void Controller::closeSDL() {
    IMG_Quit();
    SDL_Quit();
}

int Controller::run(){

    bool quit = false;
    SDL_Event event;
    while (!quit){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) quit = true;
                //key pressed
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){
                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        game.startMovingUp();
                        break;
                    case SDLK_DOWN:
                        game.startMovingDown();
                        break;
                    case SDLK_LEFT:
                        game.startMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        game.startMovingRight();
                        break;
                    case SDLK_l:
                        game.changeLevel();
                        break;
                    case SDLK_SPACE:
                        game.startJumping();
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
                    case SDLK_SPACE:
                        game.stopJumping();
                        break;
                    default:
                        break;
                }
            }
            Message entityInfo = game.getStatus();
            while(!entityInfo.isEmpty()){
                char entityType;
                int posX;
                int posY;
                int width;
                int height;
                char state;
                entityInfo.getEntityInfo(entityType,posX,posY,width,height,state);
                view.render(posX,posY,width,height,state,entityType);
            }
        }
        game.update();
        view.refresh();
    }
    closeSDL();
    return 0;
}