#include "Character.h"

#define MIDAIR 1
#define RUNNING 0

Character::Character() :
    pos_x(0),
    pos_y(0),
    vel_x(0),
    vel_y(0),
    state(RUNNING)
{}

void Character::jump(){
    state = MIDAIR;
}

void Character::runLeft(){
    vel_x = -1;
}

void Character::runRight(){
    vel_x = 1;
}

void Character::moveLeft(){
    pos_y -= 1;
}

void Character::moveRight(){
    pos_x += 1;
}

Character::~Character(){}

