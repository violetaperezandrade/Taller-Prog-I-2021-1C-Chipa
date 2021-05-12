#include "Character.h"
#define CLIMBING 2
#define JUMPING 1
#define GROUNDED 0

#define CHARACTER_CODE 'C'

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(CHARACTER_CODE, posX, posY, width, height, speedX, speedY),
    state(GROUNDED)
{}

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

