#include "StateManager.h"

#define STANDARD_MODE 'S'
#define HAMMER_MODE 'H'

#define FALLING_RIGHT '1'
#define FALLING_LEFT '2'
#define MOVING_RIGHT '6'
#define MOVING_LEFT '7'
#define MOVING_UP '8'
#define MOVING_DOWN '9'
#define IDLE_RIGHT 'r'
#define IDLE_LEFT 'l'
#define IDLE_OFF 'd'

#define HAMMER_FALLING_RIGHT 'A'
#define HAMMER_FALLING_LEFT 'B'
#define HAMMER_MOVING_RIGHT 'C'
#define HAMMER_MOVING_LEFT 'D'
#define HAMMER_MOVING_UP 'E'
#define HAMMER_MOVING_DOWN 'F'
#define HAMMER_IDLE_RIGHT 'G'
#define HAMMER_IDLE_LEFT 'H'
#define HAMMER_IDLE_OFF 'I'

StateManager::StateManager() : mode(STANDARD_MODE){}
StateManager::~StateManager(){}
void StateManager::setStandardMode(){
    mode = STANDARD_MODE;
}

void StateManager::setHammerMode(){
    mode = HAMMER_MODE;
}

char StateManager::getFallingRight(){
    if (mode == HAMMER_MODE){
        return HAMMER_FALLING_RIGHT;
    }
    return FALLING_RIGHT;
}

char StateManager::getFallingLeft(){
    if (mode == HAMMER_MODE){
        return HAMMER_FALLING_LEFT;
    }
    return FALLING_LEFT;
}

char StateManager::getMovingRight(){
    if (mode == HAMMER_MODE){
        return HAMMER_MOVING_RIGHT;
    }
    return MOVING_RIGHT;
}

char StateManager::getMovingLeft(){
    if (mode == HAMMER_MODE){
        return HAMMER_MOVING_LEFT;
    }
    return MOVING_LEFT;
}

char StateManager::getMovingUp(){
    if (mode == HAMMER_MODE){
        return HAMMER_MOVING_UP;
    }
    return MOVING_UP;
}

char StateManager::getMovingDown(){
    if (mode == HAMMER_MODE){
        return HAMMER_MOVING_DOWN;
    }
    return MOVING_DOWN;
}

char StateManager::getIdleRight(){
    if (mode == HAMMER_MODE){
        return HAMMER_IDLE_RIGHT;
    }
    return IDLE_RIGHT;
}

char StateManager::getIdleLeft(){
    if (mode == HAMMER_MODE){
        return HAMMER_IDLE_LEFT;
    }
    return IDLE_LEFT;
}

char StateManager::getIdleOff(){
    if (mode == HAMMER_MODE){
        return HAMMER_IDLE_OFF;
    }
    return IDLE_OFF;
}