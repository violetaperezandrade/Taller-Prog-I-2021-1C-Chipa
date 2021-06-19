#include "Fire.h"

#define FIRE_CODE 'F'
#define FIRE_STATE 'F'

Fire::Fire(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(FIRE_CODE, posX, posY, width, height, speedX, speedY,'P')
{}

Fire::~Fire(){}

char Fire::getState() {
    return FIRE_STATE;
}