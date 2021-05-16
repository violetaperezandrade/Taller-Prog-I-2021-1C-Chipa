#include "Flame.h"

#define FLAME_CODE 'f'
#define FLAME_STATE '0'

Flame::Flame(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(FLAME_CODE, posX, posY, width, height, speedX, speedY)
{}

Flame::~Flame(){}

char Flame::getState() {
    return FLAME_STATE;
}
