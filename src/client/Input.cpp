#include "Input.h"
#include "../common/protocols/InputProtocol.h"

Input::Input(Socket& socket) : socket(socket),quit(false){}

void Input::run() {
    SDL_Event e;
    while(!quit){
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        InputProtocol::sendPressUpEvent(socket);
                        break;
                    case SDLK_DOWN:
                        InputProtocol::sendPressDownEvent(this->socket);
                        break;
                    case SDLK_LEFT:
                        InputProtocol::sendPressLeftEvent(this->socket);
                        break;
                    case SDLK_RIGHT:
                        InputProtocol::sendPressRightEvent(this->socket);
                        break;
                    case SDLK_SPACE:
                        InputProtocol::sendPressJumpEvent(this->socket);
                        break;
                    default:
                        break;
                }
            }
            else if(e.type == SDL_KEYUP && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        InputProtocol::sendReleaseUpEvent(this->socket);
                        break;
                    case SDLK_DOWN:
                        InputProtocol::sendReleaseDownEvent(this->socket);
                        break;
                    case SDLK_LEFT:
                        InputProtocol::sendReleaseLeftEvent(this->socket);
                        break;
                    case SDLK_RIGHT:
                        InputProtocol::sendReleaseRightEvent(this->socket);
                        break;
                    case SDLK_SPACE:
                        InputProtocol::sendReleaseJumpEvent(this->socket);
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
    this->socket.shutdownWrite();
}

Input::~Input(){
}