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
#define DEATH 'x'

Character::Character(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(CHARACTER_CODE, posX, posY, width, height, speedX, speedY, IDLE_RIGHT, 'T'),
    movement(), lastDirection('r'), lives(3), points(0), silenced(false), invincible(false)
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

void Character::setInvincible() {
    invincible = true;
}

bool Character::isInvincible() {
    return invincible;
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
            state = stateManager.getFallingLeft();
            lastDirection = IDLE_LEFT;
        } else if (movement.isMovingRight()){
            speedX = config.getMovingSpeed();
            state = stateManager.getFallingRight();
            lastDirection = IDLE_RIGHT;
        } else {
            if (lastDirection == IDLE_RIGHT){
                state = stateManager.getFallingRight();
            } else {
                state = stateManager.getFallingLeft();
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
            state = stateManager.getMovingUp();
        } else if (movement.shouldMoveDown()){
            speedX = 0;
            speedY = config.getClimbingSpeed();
            state = stateManager.getMovingDown();
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
        state = stateManager.getMovingLeft();
        lastDirection = IDLE_LEFT;
    } else if (movement.shouldMoveRight()){
        speedX = config.getMovingSpeed();
        state = stateManager.getMovingRight();
        lastDirection = IDLE_RIGHT;
    } else {
        speedX = 0;
        if (state != IDLE_OFF){
            if (lastDirection == IDLE_RIGHT){
                state = stateManager.getIdleRight();
            } else {
                state = stateManager.getIdleLeft();
            }
        }
    }
}

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

void Character::updateStatus(Config& config){
    if(!this->isSilenced()){
        if (movement.isMidair()) {
            speedY += config.getGravity();
        } else if (movement.isClimbing()) {
            attemptClimb(config);
        } else {
            attemptJump(config);
            attemptClimb(config);
            attemptGroundMovement(config);
        }
    }
}

void Character::disconnect() {
    movement.setJumping(false);
    movement.setMovingDown(false);
    movement.setMovingUp(false);
    movement.setMovingLeft(false);
    movement.setMovingRight(false);
    if (!isDead()){
        state = stateManager.getIdleOff();
    }
}

void Character::reconnect() {
    movement.setJumping(false);
    movement.setMovingDown(false);
    movement.setMovingUp(false);
    movement.setMovingLeft(false);
    movement.setMovingRight(false);
    if (isDead()) {
        state = DEATH;
        silenced = true;
    } else if (lastDirection == IDLE_RIGHT){
        state = stateManager.getIdleRight();
    } else {
        state = stateManager.getIdleLeft();
    };

}

void Character::loseLive(){
    if(invincible) return;
    lives--;
    posX = 5;
    posY = 544;
    if(lives == 0){
        this->silence();
        state = DEATH;
    }
}

void Character::addPoints(int i){
    points += i;
}

int Character::getLives(){
    return lives;
}

int Character::getPoints(){
    return points;
}

void Character::pickUpHammer(){
    hammerUsages = 3;
    stateManager.setHammerMode();
}

void Character::useHammer(){
    hammerUsages--;
    if (hammerUsages == 0){
        stateManager.setStandardMode();
    }
}

bool Character::hasHammer(){
    return hammerUsages > 0;
}

void Character::silence(){
    silenced = true;
    state = stateManager.getIdleRight();
}

void Character::unsilence(){
    silenced = false;
}

bool Character::isSilenced(){
    return silenced;
}

bool Character::isDead(){
    return lives == 0;
}

Character::~Character(){}

