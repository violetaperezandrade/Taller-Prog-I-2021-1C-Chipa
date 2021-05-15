#include "Princess.h"

#define PRINCESS_CODE 'p'

Princess::Princess(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(PRINCESS_CODE, posX, posY, width, height, speedX, speedY)
{}

Princess::~Princess(){}
