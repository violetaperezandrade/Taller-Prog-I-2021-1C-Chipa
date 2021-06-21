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
#define IDLE_OFF 'd'

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(CHARACTER_CODE, posX, posY, width, height, speedX, speedY, MOVING_RIGHT, 'T'),
    movement(), lastDirection('r')
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

void Character::attemptJump(Config& config){
    if (movement.attemptJump()){
        speedY = -config.getJumpingSpeed();
        if (movement.isMovingLeft()){
            speedX = -config.getMovingSpeed();
            state = FALLING_LEFT;
            lastDirection = IDLE_LEFT;
        } else if (movement.isMovingRight()){
            speedX = config.getMovingSpeed();
            state = FALLING_RIGHT;
            lastDirection = IDLE_RIGHT;
        } else {
            if (lastDirection == IDLE_RIGHT){
                state = FALLING_RIGHT;
            } else {
                state = FALLING_LEFT;
            }
        }
    }
}

void Character::land(){
    movement.land();
    speedY = 0;
}

void Character::attemptClimb(Config& config){
    if (movement.attemptClimb() || movement.isClimbing()){
        if (movement.shouldMoveUp()){
            speedX = 0;
            speedY = -config.getClimbingSpeed();
            state = MOVING_UP;
        } else if (movement.shouldMoveDown()){
            speedX = 0;
            speedY = config.getClimbingSpeed();
            state = MOVING_DOWN;
        } else {
            speedY = 0;
        }
    }
}

void Character::attemptGroundMovement(Config& config){
    if (!movement.isGrounded()){
        return;
    }
    if (movement.shouldMoveLeft()){
        speedX = -config.getMovingSpeed();
        state = MOVING_LEFT;
        lastDirection = IDLE_LEFT;
    } else if (movement.shouldMoveRight()){
        speedX = config.getMovingSpeed();
        state = MOVING_RIGHT;
        lastDirection = IDLE_RIGHT;
    } else {
        speedX = 0;
        if (lastDirection == IDLE_RIGHT){
            state = IDLE_RIGHT;
        } else {
            state = IDLE_LEFT;
        }
    }
}

/*
bool Character::isOnStairs(){
    return movement.isOnStairs();
}*/

bool Character::isTryingToClimb() {
    return movement.isTryingToClimb();
}

void Character::setOnStairs(bool value){
    movement.setOnStairs(value);
}

void Character::setFalling(){
    movement.setFalling();
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

/*void Character::updateStatus(Config& config){
    if (movement.isMidair()){
        speedY += config.getGravity();
    } else if (movement.shouldMoveUp()){
        state = MOVING_UP;
        speedY = -config.getClimbingSpeed();
    } else if (movement.shouldMoveDown()){
        state = MOVING_DOWN;
        speedY = config.getClimbingSpeed();
    } else if (movement.shouldClimb()) {
        state = MOVING_UP;
    } else {
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
}*/

void Character::updateStatus(Config& config){
    if (movement.isMidair()){
        speedY += config.getGravity();
    } else if (movement.isClimbing()){
        attemptClimb(config);
    } else {
        attemptJump(config);
        attemptClimb(config);
        attemptGroundMovement(config);
    }
}

void Character::disconnect() {
    movement.setJumping(false);
    movement.setMovingDown(false);
    movement.setMovingUp(false);
    movement.setMovingLeft(false);
    movement.setMovingRight(false);
    state = IDLE_OFF;
}

Character::~Character(){}

