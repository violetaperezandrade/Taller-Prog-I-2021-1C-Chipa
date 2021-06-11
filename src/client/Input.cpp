#include "Input.h"
void run(){
    SDL_Event e;
    char msg;
    while(!quit){
        while(SDL_WaitEvent(&e) != 0){
            if(e.type == SDL_KEYDOWN){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        msg = 1;
                        break;
                    case SDLK_DOWN:
                        msg = 3;
                        break;
                    case SDLK_LEFT:
                        msg = 5;
                        break;
                    case SDLK_RIGHT:
                        msg = 7;
                        break;
                    case SDLK_SPACE:
                        msg = 9;
                        break;
                    default:
                        break;
                }
            }
            else if(e.type == SDL_KEYUP){
                switch(e.key.keysym.sym){
                    case SDLK_UP:
                        msg = 2;
                        break;
                    case SDLK_DOWN:
                        msg = 4;
                        break;
                    case SDLK_LEFT:
                        msg = 6;
                        break;
                    case SDLK_RIGHT:
                        msg = 8;
                        break;
                    case SDLK_SPACE:
                        msg = 10;
                        break;
                    default:
                        break;
                }
            }
            this->socket.send(msg, 1);
        }