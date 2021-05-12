#include "Fire.h"

#define FIRE_CODE 'F'

Fire::Fire(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(FIRE_CODE, posX, posY, width, height, speedX, speedY)
{}

Fire::~Fire(){}