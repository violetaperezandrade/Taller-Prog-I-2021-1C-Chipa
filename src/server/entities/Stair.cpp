#include "Stair.h"

#define STAIR_CODE 'S'
#define STAIR_STATE '0'

Stair::Stair(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(STAIR_CODE, posX, posY, width, height, speedX, speedY, STAIR_STATE, 'P')
{}

Stair::~Stair(){}