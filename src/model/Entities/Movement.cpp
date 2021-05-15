#include "Movement.h"

bool movingLeft;
bool movingRight;
bool movingUp;
bool movingDown;
bool jumping;
bool midair;
bool onStairs;

Movement::Movement() : movingLeft(false), movingRight(false), movingUp(false),
                       movingDown(false),  jumping(false), midair(false),
                       onStairs(false) {}
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
void Movement::setOnStairs(bool value){
    onStairs = value;
}

bool Movement::shouldMoveLeft(){
    return !midair && !onStairs && !movingRight && movingLeft;
}
bool Movement::shouldMoveRight(){
    return !midair && !onStairs && !movingLeft && movingRight;
}
bool Movement::shouldMoveUp(){
    return !midair && onStairs && !movingDown && movingUp;
}
bool Movement::shouldMoveDown(){
    return !midair && onStairs && !movingUp && movingDown;
}
bool Movement::shouldJump(){
    return !midair && !onStairs && jumping;
}
bool Movement::shouldFall(){
    return midair;
}
bool Movement::shouldGetOnStairs(){
    return !midair && !onStairs && (movingUp || movingDown);
}