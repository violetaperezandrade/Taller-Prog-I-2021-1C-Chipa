#include "Character.h"
#define CLIMBING 2
#define JUMPING 1
#define GROUNDED 0

#define CHARACTER_CODE 'C'

#define FALLING_RIGHT '1'
#define FALLING_LEFT '2'
#define MOVING_RIGHT '6'
#define MOVING_LEFT '7'
#define MOVING_UP '8'
#define MOVING_DOWN '9'
#define IDLE_RIGHT 'r'
#define IDLE_LEFT 'l'

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(CHARACTER_CODE, posX, posY, width, height, speedX, speedY,'0'),
    state(GROUNDED), movement(), lastDirection('r')
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
    movement.setClimbing(false);
    speedY = 0;
}

void Character::climb(){
    if (movement.shouldClimb()){
        movement.setClimbing(true);
    }
}

bool Character::isGrounded(){
    return !movement.isMidair() && !movement.isClimbing();
}

bool Character::isClimbing(){
    return movement.isClimbing();
}

bool Character::isMidair(){
    return movement.isMidair();
}

/*
void Character::updateStatus(){
    if (movement.shouldFall() && movement.shouldMoveRight()){
        state = FALLING_RIGHT;
        speedX = 20;//config.getMoveSpeed();
    } else if (movement.shouldFall() && movement.shouldMoveLeft()){
        state = FALLING_LEFT;
        speedX = -20;//config.getMoveSpeed();
    } else if (movement.shouldFall()){
        state = FALLING_STRAIGHT;
    }// else if (movement.shouldGetOnStairs()){
        //state = ABOUT_TO_CLIMB;
    } else if (movement.shouldJump()){
        state = ABOUT_TO_JUMP;
        movement.setMidair(true);
        speedY = -20;//config.getJumpSpeed();
    } else if (movement.shouldMoveRight()){
        state = MOVING_RIGHT;
        speedX = 20;//config.getMoveSpeed();
    } else if (movement.shouldMoveLeft()){
        state = MOVING_LEFT;
        speedX = -20;//config.getMoveSpeed();
    } else if (movement.shouldMoveUp()){
        state = MOVING_UP;
    } else if (movement.shouldMoveDown()) {
        state = MOVING_DOWN;
    } else {
        state = IDLE_BACK;
    }
}*/

void Character::updateStatus(Config& config){
    if (movement.shouldFall()){
        speedY += config.getGravity();
    }/* else if (movement.shouldC()) {
        state = MOVING_UP;
        if (movement.shouldMoveUp()){
            speedY = -config.getClimbSpeed();
        } else if (movement.shouldMoveDown()){
            state = MOVING_DOWN;
            speedY = config.getClimbSpeed();
        }
    }*/ else {
        if (movement.shouldMoveRight()){
            state = MOVING_RIGHT;
            speedX = config.getMovingSpeed();
            if (movement.shouldJump()){
                state = FALLING_RIGHT;
                movement.setMidair(true);
                speedY = -config.getJumpingSpeed();
            }
            lastDirection = 'r';
        } else if (movement.shouldMoveLeft()){
            state = MOVING_LEFT;
            speedX = -config.getMovingSpeed();
            if (movement.shouldJump()){
                state = FALLING_LEFT;
                movement.setMidair(true);
                speedY = -config.getJumpingSpeed();
            }
            lastDirection = 'l';
        } else {
            speedX = 0;
            if (lastDirection == 'l'){
                state = IDLE_LEFT;
                if (movement.shouldJump()){
                    state = FALLING_LEFT;
                    movement.setMidair(true);
                    speedY = -config.getJumpingSpeed();
                }
            } else {
                state = IDLE_RIGHT;
                if (movement.shouldJump()){
                    state = FALLING_RIGHT;
                    movement.setMidair(true);
                    speedY = -config.getJumpingSpeed();
                }
            }
            //use lastMovementDirection to chose what idle sprite to use

        }
    }
}

char Character::getState() {
    return state;
}

Character::~Character(){}

