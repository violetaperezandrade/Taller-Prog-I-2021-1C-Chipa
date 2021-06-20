#include "Fire.h"

#define FIRE_CODE 'F'
#define FIRE_STATE '0'

Fire::Fire(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(FIRE_CODE, posX, posY, width, height, speedX, speedY, FIRE_STATE,'P')
{}

Fire::~Fire(){}