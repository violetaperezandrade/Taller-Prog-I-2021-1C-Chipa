#include "Platform.h"
#include <iostream>

#define PLATFORM_CODE 'P'
#define PLATFORM_STATE 'P'

Platform::Platform(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(PLATFORM_CODE, posX, posY, width, height, speedX, speedY,'P')
{
    std::cout<< speedX;
    if(speedX != 0){
        setPermanency('T');
    }
}

Platform::~Platform(){}

char Platform::getState() {
    return PLATFORM_STATE;
}
