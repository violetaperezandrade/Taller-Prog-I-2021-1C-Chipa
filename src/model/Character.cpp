#include "Character.h"

#define MIDAIR 1
#define RUNNING 0

Character::Character() :
    posX(0),
    posY(0),
    speedX(0),
    speedY(0),
    state(RUNNING)
{}

void Character::jump(){
    state = MIDAIR;
}

void Character::runLeft(){
    speedX = -1;
}

void Character::runRight(){
    speedX = 1;
}

void Character::moveLeft(int& i){
    posX -= i;
}

void Character::moveRight(int& i){
    posX += i;
}

Character::~Character(){}

