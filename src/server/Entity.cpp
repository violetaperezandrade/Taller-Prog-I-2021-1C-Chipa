#include "Entity.h"

Entity::Entity(char type, int posX, int posY, int width, int height) :
    type(type),
    posX(posX),
    posY(posY),
    width(width),
    height(height),
    speedX(0),
    speedY(0),
{}

Entity::Entity(char type, int posX, int posY,
               int width, int height, int speedX, int speedY, char permanency) :
    type(type),
    posX(posX),
    posY(posY),
    width(width),
    height(height),
    speedX(speedX),
    speedY(speedY),
    permanency(),
{}

void Entity::setPosY(int i){
    posY = i;
}

void Entity::setPosX(int i){
    posX = i;
}

void Entity::setSpeedX(int i){
    speedX = i;
}

void Entity::setSpeedY(int i){
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

int Entity::getWidth(){
    return width;
}

int Entity::getHeight(){
    return height;
}

char Entity::getType() {
    return type;
}

char Entity::getState(){
    return '0';
}

char Entity::getPermanency() {
    return permanency;
}

char Entity::setPermanency(char c) {
    permanency = c;
}

Entity::~Entity(){}
//virtual Entity::~Entity(){}

