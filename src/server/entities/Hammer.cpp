#include "Hammer.h"

#define HAMMER_CODE 'H'
#define HAMMER_STATE '0'

Hammer::Hammer(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(HAMMER_CODE, posX, posY, width, height, speedX, speedY, HAMMER_STATE,'T')
{}

Hammer::~Hammer(){}