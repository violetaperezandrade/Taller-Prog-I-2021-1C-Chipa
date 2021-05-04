#include "Character.h"

#define MIDAIR 1
#define RUNNING 0

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(int posX, int posY, int width, int height, int speedX, int speedY),
    state(RUNNING)
{}

void Character::jump(){
    state = JUMPING;
}

void Character::land(){
    state = RUNNING;
}

bool Character::isJumping(){
    return state == MIDAIR;
}

Character::~Character(){}

