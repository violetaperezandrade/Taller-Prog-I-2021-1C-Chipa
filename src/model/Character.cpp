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

void Character::moveLeft(int& i){
    posX -= i;
}

void Character::moveRight(int& i){
    posX += i;
}

Character::~Character(){}

