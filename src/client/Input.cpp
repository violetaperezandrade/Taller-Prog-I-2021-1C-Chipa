#include "Input.h"
#include "../common/protocols/InputProtocol.h"

Input::Input(Socket& socket, Logger& logger, bool& keepRunning, bool& serverActive, bool& play) :
        socket(socket),
        keepRunning(keepRunning),
        logger(logger),
        serverActive(serverActive),
        play(play)
{}

void Input::run() {
    int success;
    SDL_Event e;
    while(keepRunning && serverActive){
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_QUIT) {
                logger.debugMsg("Se cierra la ventana desde el input", __FILE__, __LINE__);
                keepRunning = false;
                break;
            }
            else if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        success = InputProtocol::sendPressUpEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_DOWN:
                        success = InputProtocol::sendPressDownEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_LEFT:
                        success = InputProtocol::sendPressLeftEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_RIGHT:
                        success = InputProtocol::sendPressRightEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_SPACE:
                        success = InputProtocol::sendPressJumpEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_p:
                        play = !play;
                        break;
                    case SDLK_i:
                        success = InputProtocol::sendInvincibility(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                    default:
                        break;
                }
            }
            else if(e.type == SDL_KEYUP && e.key.repeat == 0){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        success = InputProtocol::sendReleaseUpEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_DOWN:
                        success = InputProtocol::sendReleaseDownEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_LEFT:
                        success = InputProtocol::sendReleaseLeftEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_RIGHT:
                        success = InputProtocol::sendReleaseRightEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    case SDLK_SPACE:
                        success = InputProtocol::sendReleaseJumpEvent(this->socket, this->logger);
                        if (success < 0){
                            serverActive = false;
                            logger.superDebugMsg("Inactive server", __FILE__, __LINE__);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
}

void Input::stop(){
    logger.debugMsg("Stop input sender", __FILE__, __LINE__);
    keepRunning = false;
    this->socket.shutdown(logger);
}

Input::~Input(){}