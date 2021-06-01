#include "Controller.h"
#include <string>
#define FRAME_TIME 33

Controller::Controller(Config& config, Logger& logger):config(config), game(config, logger), view(game,logger, config), logger(logger){}
Controller::~Controller(){}



int Controller::run(){

    bool quit = false;
    SDL_Event event;
    view.renderFilledQuad();
    //Timer counters
    Uint32 initial_time;
    Uint32 final_time;
    while (quit == false){
        logger.debugMsg("Inicia gameloop", __FILE__, __LINE__);

        initial_time = SDL_GetTicks();
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) {
                logger.debugMsg("Botón QUIT", __FILE__, __LINE__);
                quit = true;
            }
                //key pressed
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){

                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        logger.debugMsg("Se presiona boton UP", __FILE__, __LINE__);
                        game.startMovingUp();
                        break;
                    case SDLK_DOWN:
                        logger.debugMsg("Se presiona boton DOWN", __FILE__, __LINE__);
                        game.startMovingDown();
                        break;
                    case SDLK_LEFT:
                        logger.debugMsg("Se presiona boton LEFT", __FILE__, __LINE__);
                        game.startMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        logger.debugMsg("Se presiona boton RIGHT", __FILE__, __LINE__);
                        game.startMovingRight();
                        break;
                    case SDLK_l:
                        logger.debugMsg("Tecla de cambio de nivel", __FILE__, __LINE__);
                        game.changeLevel();
                        view.changeLevel();
                        break;
                    case SDLK_SPACE:
                        logger.debugMsg("Se presiona boton SPACE", __FILE__, __LINE__);
                        game.startJumping();
                        break;
                    default:
                        break;
                }
            }
            else if(event.type == SDL_KEYUP && event.key.repeat == 0){

                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        logger.debugMsg("Se libera boton UP", __FILE__, __LINE__);
                        game.stopMovingUp();
                        break;
                    case SDLK_DOWN:
                        logger.debugMsg("Se libera boton DOWN", __FILE__, __LINE__);
                        game.stopMovingDown();
                        break;
                    case SDLK_LEFT:
                        logger.debugMsg("Se libera boton LEFT", __FILE__, __LINE__);
                        game.stopMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        logger.debugMsg("Se libera boton RIGHT", __FILE__, __LINE__);
                        game.stopMovingRight();
                        break;
                    case SDLK_SPACE:
                        logger.debugMsg("Se libera boton SPACE", __FILE__, __LINE__);
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
        int frameTime = config.getFrameTime();
        if (used_time < frameTime) {
            SDL_Delay(frameTime - used_time);
        }
    }
    return 0;
}