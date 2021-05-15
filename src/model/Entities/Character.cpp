#include "Character.h"
#define CLIMBING 2
#define JUMPING 1
#define GROUNDED 0

#define CHARACTER_CODE 'C'

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(CHARACTER_CODE, posX, posY, width, height, speedX, speedY),
    state(GROUNDED)
{}

void Character::startMovingLeft(){
    state = GROUNDED;
}

void Character::startMovingRight(){
    state = GROUNDED;
}

void Character::startMovingUp(){
    state = GROUNDED;
}

void Character::startMovingDown(){
    state = GROUNDED;
}

void Character::startJumping(){
    state = GROUNDED;
}

void Character::stopMovingLeft(){
    state = GROUNDED;
}

void Character::stopMovingRight(){
    state = GROUNDED;
}

void Character::stopMovingUp(){
    state = GROUNDED;
}

void Character::stopMovingDown(){
    state = GROUNDED;
}

void Character::stopJumping(){
    state = GROUNDED;
}

void Character::jump(){
    state = JUMPING;
}

void Character::land(){
    state = GROUNDED;
}

void Character::climb(){
    state = CLIMBING;
}

bool Character::isGrounded(){
    return state == GROUNDED;
}

bool Character::isClimbing(){
    return state == CLIMBING;
}

Character::~Character(){}

