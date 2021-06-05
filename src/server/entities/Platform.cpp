#include "Platform.h"

#define PLATFORM_CODE 'P'
#define PLATFORM_STATE 'P'

Platform::Platform(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(PLATFORM_CODE, posX, posY, width, height, speedX, speedY,'1')
{
    if(posX != 0){
        setPermanency('0');
    }
}

Platform::~Platform(){}

char Platform::getState() {
    return PLATFORM_STATE;
}
