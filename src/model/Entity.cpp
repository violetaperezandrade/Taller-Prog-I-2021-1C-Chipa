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

Entity::~Entity(){}