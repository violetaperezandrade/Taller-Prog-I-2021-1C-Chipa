#include "Barrel.h"

#define BARREL_CODE 'B'
#define BARREL_STATE '0'

Barrel::Barrel(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(BARREL_CODE, posX, posY, width, height, speedX, speedY)
{}

Barrel::~Barrel(){}

char Barrel::getState() {
    return BARREL_STATE;
}
