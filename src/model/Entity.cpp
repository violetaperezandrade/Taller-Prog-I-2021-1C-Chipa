#include "Entity.h"

Entity::Entity(int posX, int posY, int width, int height) :
    posX(posX),
    posY(posY),
    width(width),
    height(height),
    speedX(0),
    speedY(0)
{}

Entity::Entity(int posX, int posY, int width, int height, int speedX, int speedY) :
    posX(posX),
    posY(posY),
    width(width),
    height(height),
    speedX(speedX),
    speedY(speedY)
{}

void Entity::setPosY(int& i){
    posY = i;
}

void Entity::setPosX(int& i){
    posX = i;
}

void Entity::setSpeedX(int& i){
    speedX = i;
}

void Entity::setSpeedY(int& i){
    speedY = i;
}

int Entity::getPosY(){
    return posY;
}

int Entity::getPosX(){
    return posX;
}

int Entity::getSpeedX(){
    return speedX;
}

int Entity::getSpeedY(){
    return speedY;
}

virtual Entity::~Entity(){}

void Entity::handleEvent(SDL_Event& e){

    if(e.type == SDL_KEYDOWN && e.key.repeat == 0){
        //modify vel
        switch(e.key.keysym.sym){
            case SDLK_UP:
                speedY -= ENTITYSPEED;
                break;
            case SDLK_DOWN:
                speedY += ENTITYSPEED;
                break;
            case SDLK_LEFT:
                speedX -= ENTITYSPEED;
                break;
            case SDLK_RIGHT:
                speedX += ENTITYSPEED;
                break;
        }
    }
    if(e.type == SDL_KEYUP && e.key.repeat == 0){
        switch(e.key.keysym.sym){
            case SDLK_UP:
                speedY += ENTITYSPEED;
                break;
            case SDLK_DOWN:
                speedY -= ENTITYSPEED;
                break;
            case SDLK_LEFT:
                speedX += ENTITYSPEED;
                break;
            case SDLK_RIGHT:
                speedX -= ENTITYSPEED;
                break;
        }
    }
}

void Entity::move(){
    posX += speedX;
    if((posX < 0) || (posX + width > SCREEN_WIDTH)) posX -= speedX;

    posY += speedY;
    if((posY < 0) || (posY + height > SCREEN_HEIGHT)) posY -= speedY;
}