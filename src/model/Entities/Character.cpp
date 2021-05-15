#include "Character.h"
#define CLIMBING 2
#define JUMPING 1
#define GROUNDED 0

#define CHARACTER_CODE 'C'

#define FALLING_RIGHT '1'
#define FALLING_LEFT '2'
#define FALLING_STRAIGHT '3'
#define ABOUT_TO_CLIMB '4'
#define ABOUT_TO_JUMP '5'
#define MOVING_RIGHT '6'
#define MOVING_LEFT '7'
#define MOVING_UP '8'
#define MOVING_DOWN '9'
#define IDLE_BACK '0'
#define IDLE_RIGHT 'r'
#define IDLE_LEFT 'l'

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(CHARACTER_CODE, posX, posY, width, height, speedX, speedY),
    state(GROUNDED), movement()
{}

void Character::startMovingLeft(){
    movement.setMovingLeft(true);
}

void Character::startMovingRight(){
    movement.setMovingRight(true);
}

void Character::startMovingUp(){
    movement.setMovingUp(true);
}

void Character::startMovingDown(){
    movement.setMovingDown(true);
}

void Character::startJumping(){
    movement.setJumping(true);
}

void Character::stopMovingLeft(){
    movement.setMovingLeft(false);
}

void Character::stopMovingRight(){
    movement.setMovingRight(false);
}

void Character::stopMovingUp(){
    movement.setMovingUp(false);
}

void Character::stopMovingDown(){
    movement.setMovingDown(false);
}

void Character::stopJumping(){
    movement.setJumping(false);
}

void Character::jump(){
    if (movement.shouldJump()){
        movement.setMidair(true);
    }
}

void Character::land(){
    movement.setMidair(false);
    movement.setOnStairs(false);
}

void Character::climb(){
    if (movement.shouldGetOnStairs()){
        movement.setOnStairs(true);
    }
}

void Character::updateStatus(){
    if (movement.shouldFall() && movement.shouldMoveRight()){
        status = FALLING_RIGHT;
    } else if (movement.shouldFall() && movement.shouldMoveLeft()){
        status = FALLING_LEFT;
    } else if (movement.shouldFall()){
        status = FALLING_STRAIGHT;
    } else if (movement.shouldGetOnStairs()){
        status = ABOUT_TO_CLIMB;
    } else if (movement.shouldJump()){
        status = ABOUT_TO_JUMP;
        movement.setMidair(true);
        speedY = config.getJumpSpeed();
    } else if (movement.shouldMoveRight()){
        status = MOVING_RIGHT;
    } else if (movement.shouldMoveLeft()){
        status = MOVING_LEFT;
    } else if (movement.shouldMoveUp()){
        status = MOVING_UP;
    } else if (movement.shouldMoveDown()) {
        status = MOVING_DOWN;
    } else {
        status = IDLE;
    }
}

Character::~Character(){}

