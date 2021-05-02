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

void Character::run_left(){
    vel_x = -1;
}

void Character::run_right(){
    vel_x = 1;
}

void Character::move_left(){
    pos_y -= 1;
}

void Character::move_right(){
    pos_x += 1;
}

Character::~Character(){}

