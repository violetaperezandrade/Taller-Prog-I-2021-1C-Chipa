#include "Platform.h"

#define PLATFORM_CODE 'P'
#define PLATFORM_STATE '0'

Platform::Platform(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(PLATFORM_CODE, posX, posY, width, height, speedX, speedY, PLATFORM_STATE,'P')
{
    if(speedX != 0){
        setPermanency('T');
    }
}

Platform::~Platform(){}
