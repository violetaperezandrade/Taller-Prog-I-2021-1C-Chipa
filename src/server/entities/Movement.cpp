#include "Movement.h"

Movement::Movement() : movingLeft(false), movingRight(false), movingUp(false),
                       movingDown(false),  jumping(false), midair(false),
                       climbing(false),onStairs(false) {}
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
void Movement::setJumping(bool value){
    jumping = value;
}
void Movement::setMidair(bool value){
    midair = value;
}
void Movement::setClimbing(bool value){
    climbing = value;
}

void Movement::setOnStairs(bool value){
    onStairs = value;
}

bool Movement::isMidair() {
    return midair;
}

bool Movement::isClimbing() {
    return climbing;
}

bool Movement::isOnStairs() {
    return onStairs;
}

bool Movement::isTryingToClimb() {
    return movingUp || movingDown;
}

bool Movement::shouldMoveLeft(){
    return !midair && !climbing && !movingRight && movingLeft;
}
bool Movement::shouldMoveRight(){
    return !midair && !climbing && !movingLeft && movingRight;
}
bool Movement::shouldMoveUp(){
    return !midair && climbing && !movingDown && movingUp;
}
bool Movement::shouldMoveDown(){
    return !midair && climbing && !movingUp && movingDown;
}
bool Movement::shouldJump(){
    return !midair && !climbing && jumping;
}
bool Movement::shouldFall(){
    return midair;
}
bool Movement::shouldClimb(){
    return !midair && onStairs && (movingUp || movingDown);
}