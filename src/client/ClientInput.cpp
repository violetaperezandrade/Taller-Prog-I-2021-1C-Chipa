#include "ClientInput.h"
#include "../common/protocols/InputProtocol.h"

ClientInput::ClientInput(Socket socket) : socket(socket){}

void ClientInput::run() {

    bool quit = false;
    while(!quit){
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_QUIT) quit = true;
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        InputProtocol::sendPressUpEvent(this->socket);
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
            else if(e::type == SDL_KEYUP){
                switch(e::key::keysym::sym){
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
