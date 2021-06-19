#include "Princess.h"

#define PRINCESS_CODE 'p'
#define PRINCESS_STATE '0'

Princess::Princess(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(PRINCESS_CODE, posX, posY, width, height, speedX, speedY,'P')
{}

Princess::~Princess(){}

char Princess::getState() {
    return PRINCESS_STATE;
}
