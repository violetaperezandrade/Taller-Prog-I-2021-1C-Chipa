#include "Movement.h"

#define MIDAIR 'M'
#define CLIMBING 'C'
#define GROUNDED 'G'

Movement::Movement() : state(GROUNDED), movingLeft(false), movingRight(false), movingUp(false),
                       movingDown(false), jumping(false), onStairs(false) {}
Movement::~Movement() {}

void Movement::setMovingLeft(bool value){
    movingLeft = value;
}
void Movement::setMovingRight(bool value){
    movingRight = value;
}
void Movement::setMovingUp(bool value){
    movingUp = value;
}
void Movement::setMovingDown(bool value){
    movingDown = value;
}

void Movement::setJumping(bool value) {
    jumping = value;
}
bool Movement::attemptJump() {
    if (state == GROUNDED && jumping){
        state = MIDAIR;
        return true;
    }
    return false;
}

bool Movement::attemptClimb() {
    if (state == GROUNDED && (movingUp != movingDown) && onStairs){ // != is xor for bool
        state = CLIMBING;
        return true;
    }
    return false;
}

void Movement::land() {
    state = GROUNDED;
}

void Movement::setOnStairs(bool value){
    onStairs = value;
    if (!onStairs){
        state = GROUNDED;
    }
}

void Movement::setFalling() {
    state = MIDAIR;
}

bool Movement::isMidair() {
    return state == MIDAIR;
}

bool Movement::isClimbing() {
    return state == CLIMBING;
}

bool Movement::isGrounded() {
    return state == GROUNDED;
}
/*
bool Movement::isOnStairs() {
    return onStairs;
}*/

bool Movement::isTryingToClimb() {
    return movingUp != movingDown;
}

bool Movement::isMovingLeft(){
    return !movingRight && movingLeft;
}
bool Movement::isMovingRight(){
    return !movingLeft && movingRight;
}

bool Movement::shouldMoveLeft(){
    return (state == GROUNDED) && !movingRight && movingLeft;
}
bool Movement::shouldMoveRight(){
    return (state == GROUNDED) && !movingLeft && movingRight;
}
bool Movement::shouldMoveUp(){
    return (state == CLIMBING) && onStairs && !movingDown && movingUp;
}
bool Movement::shouldMoveDown(){
    return (state == CLIMBING) && onStairs && !movingUp && movingDown;
}
/*
bool Movement::shouldJump(){
    return state == GROUNDED;
}
bool Movement::shouldFall(){
    return state == MIDAIR;
}
bool Movement::shouldClimb(){
    return state == CLIMBING;
}*/