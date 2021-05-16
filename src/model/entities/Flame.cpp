#include "Flame.h"

#define FLAME_CODE 'f'

Flame::Flame(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(FLAME_CODE, posX, posY, width, height, speedX, speedY)
{}

Flame::~Flame(){}
