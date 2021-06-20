#include "Input.h"
#include "../common/protocols/InputProtocol.h"

Input::Input(Socket& socket, Logger& logger, SDL_Window* window) : socket(socket), quit(false), logger(logger), window(window){}

void Input::run() {
    SDL_Event e;
    while(!quit){
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_QUIT) {
                logger.debugMsg("Se cierra la ventana desde el input", __FILE__, __LINE__);
                SDL_DestroyWindow(window);
                window = NULL;
                quit = true;
            }
            if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        InputProtocol::sendPressUpEvent(this->socket, this->logger);
                        break;
                    case SDLK_DOWN:
                        InputProtocol::sendPressDownEvent(this->socket, this->logger);
                        break;
                    case SDLK_LEFT:
                        InputProtocol::sendPressLeftEvent(this->socket, this->logger);
                        break;
                    case SDLK_RIGHT:
                        InputProtocol::sendPressRightEvent(this->socket, this->logger);
                        break;
                    case SDLK_SPACE:
                        InputProtocol::sendPressJumpEvent(this->socket, this->logger);
                        break;
                    default:
                        break;
                }
            }
            else if(e.type == SDL_KEYUP && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        InputProtocol::sendReleaseUpEvent(this->socket, this->logger);
                        break;
                    case SDLK_DOWN:
                        InputProtocol::sendReleaseDownEvent(this->socket, this->logger);
                        break;
                    case SDLK_LEFT:
                        InputProtocol::sendReleaseLeftEvent(this->socket, this->logger);
                        break;
                    case SDLK_RIGHT:
                        InputProtocol::sendReleaseRightEvent(this->socket, this->logger);
                        break;
                    case SDLK_SPACE:
                        InputProtocol::sendReleaseJumpEvent(this->socket, this->logger);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Input::stop(){
    quit = true;
    this->socket.shutdown(logger);
    //this->socket.shutdownWrite(logger);
}

Input::~Input(){}