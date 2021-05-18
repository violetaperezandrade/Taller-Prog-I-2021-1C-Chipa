#include "Controller.h"
#include <string>
#define FRAME_TIME 1000
#define PATH "../log.txt"
#define DEBUG 3

Controller::Controller():game(), view(game), logger(PATH, DEBUG){
    if(initSDL()) {
        std::string str("Error al inicializar SDL");
        logger.errorMsg(str);
    }
    else {
        std::string str("SDL Inicializado");
        logger.infoMsg(str);
    }
}
Controller::~Controller(){
    closeSDL();
}

bool Controller::initSDL() {

    bool error = false;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::string str("Fallo inicializar video SDL");
        logger.errorMsg(str);
        error = true;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        std::string str("Error al filtrar textura lineal");
        logger.errorMsg(str);
    }
    return error;
}

void Controller::closeSDL() {
    IMG_Quit();
    SDL_Quit();
    std::string str("Cerrar SDL");
    logger.infoMsg(str);
}

int Controller::run(){

    bool quit = false;
    SDL_Event event;
    view.renderFilledQuad();
    //Timer counters
    Uint32 initial_time;
    Uint32 final_time;
    while (quit == false){
        std::string str("Inicia gameloop");
        logger.debugMsg(str);

        initial_time = SDL_GetTicks();
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) {
                str.clear();
                str += "Botón QUIT";
                logger.debugMsg(str);
                quit = true;
            }
                //key pressed
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0){

                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        str.clear();
                        str += "Se preciona boton UP";
                        logger.debugMsg(str);
                        game.startMovingUp();
                        break;
                    case SDLK_DOWN:
                        str.clear();
                        str += "Se preciona boton DOWN";
                        logger.debugMsg(str);
                        game.startMovingDown();
                        break;
                    case SDLK_LEFT:
                        str.clear();
                        str += "Se preciona boton LEFT";
                        logger.debugMsg(str);
                        game.startMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        str.clear();
                        str += "Se preciona boton RIGHT";
                        logger.debugMsg(str);
                        game.startMovingRight();
                        break;
                    case SDLK_l:
                        str.clear();
                        str += "Tecla de cambio de nivel";
                        logger.debugMsg(str);
                        game.changeLevel();
                        break;
                    case SDLK_SPACE:
                        str.clear();
                        str += "Se presiona boton SPACE";
                        logger.debugMsg(str);
                        game.startJumping();
                        break;
                    default:
                        break;
                }
            }
            else if(event.type == SDL_KEYUP && event.key.repeat == 0){

                switch(event.key.keysym.sym){
                    case SDLK_UP:
                        str.clear();
                        str += "Se libera boton UP";
                        logger.debugMsg(str);
                        game.stopMovingUp();
                        break;
                    case SDLK_DOWN:
                        str.clear();
                        str += "Se libera boton DOWN";
                        logger.debugMsg(str);
                        game.stopMovingDown();
                        break;
                    case SDLK_LEFT:
                        str.clear();
                        str += "Se libera boton LEFT";
                        logger.debugMsg(str);
                        game.stopMovingLeft();
                        break;
                    case SDLK_RIGHT:
                        str.clear();
                        str += "Se libera boton RIGHT";
                        logger.debugMsg(str);
                        game.stopMovingRight();
                        break;
                    case SDLK_SPACE:
                        str.clear();
                        str += "Se libera boton SPACE";
                        logger.debugMsg(str);
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