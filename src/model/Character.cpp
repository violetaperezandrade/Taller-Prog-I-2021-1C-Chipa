#include "Character.h"

#define MIDAIR 1
#define RUNNING 0

Character::Character() :
    posX(0),
    posY(0),
    velX(0),
    velY(0),
    state(RUNNING)
{}

void Character::jump(){
    state = MIDAIR;
}

void Character::runLeft(){
    velX = -1;
}

void Character::runRight(){
    velX = 1;
}

void Character::moveLeft(){
    posX -= 1;
}

void Character::moveRight(){
    posX += 1;
}

Character::~Character(){}

