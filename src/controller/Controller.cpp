#include "Controller.h"
#include <string>
#define FRAME_TIME 1000

Controller::Controller(Logger& logger):game(logger), view(game,logger), logger(logger){
    if(initSDL()) {
        logger.errorMsg("Error al inicializar SDL");
    }
    else {
        logger.infoMsg("SDL Inicializado");
    }
}
Controller::~Controller(){
    closeSDL();
}

bool Controller::initSDL() {

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        logger.errorMsg("Fallo inicializar video SDL");
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        logger.errorMsg("Error al filtrar textura lineal");
    }
    return error;
}

void Controller::closeSDL() {
    IMG_Quit();
    SDL_Quit();
    logger.infoMsg("Cerrar SDL");
}

int Controller::run(){

    bool quit = false;
    SDL_Event event;
    view.renderFilledQuad();
    //Timer counters
    Uint32 initial_time;
    Uint32 final_time;
    while (quit == false){
        logger.debugMsg("Inicia gameloop");

        initial_time = SDL_GetTicks();
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) {
                logger.debugMsg("Botón QUIT");
                quit = true;
            }
                //key pressed
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){

                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        logger.debugMsg("Se presiona boton UP");
                        game.startMovingUp();
                        break;
                    case SDLK_DOWN:
                        logger.debugMsg("Se presiona boton DOWN");
                        game.startMovingDown();
                        break;
                    case SDLK_LEFT:
                        logger.debugMsg("Se presiona boton LEFT");
                        game.startMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        logger.debugMsg("Se presiona boton RIGHT");
                        game.startMovingRight();
                        break;
                    case SDLK_l:
                        logger.debugMsg("Tecla de cambio de nivel");
                        game.changeLevel();
                        break;
                    case SDLK_SPACE:
                        logger.debugMsg("Se presiona boton SPACE");
                        game.startJumping();
                        break;
                    default:
                        break;
                }
            }
            else if(event.type == SDL_KEYUP && event.key.repeat == 0){

                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        logger.debugMsg("Se libera boton UP");
                        game.stopMovingUp();
                        break;
                    case SDLK_DOWN:
                        logger.debugMsg("Se libera boton DOWN");
                        game.stopMovingDown();
                        break;
                    case SDLK_LEFT:
                        logger.debugMsg("Se libera boton LEFT");
                        game.stopMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        logger.debugMsg("Se libera boton RIGHT");
                        game.stopMovingRight();
                        break;
                    case SDLK_SPACE:
                        logger.debugMsg("Se libera boton SPACE");
                        game.stopJumping();
                        break;
                    default:
                        break;
                }
            }
        }
        game.update();

        view.refresh();
        final_time = SDL_GetTicks();
        Uint32 used_time = final_time - initial_time;
        if (used_time < FRAME_TIME) {
            SDL_Delay(FRAME_TIME - used_time);
            //std::cout << "Delay added of " << FRAME_TIME - used_time << "\n";
        }
    }
    return 0;
}