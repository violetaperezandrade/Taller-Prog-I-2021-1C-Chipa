#include "Barrel.h"

#define BARREL_CODE 'B'

Barrel::Barrel(int posX, int posY, int width, int height, int speedX, int speedY) :
    Entity(BARREL_CODE, posX, posY, width, height, speedX, speedY)
{}

Barrel::~Barrel(){}
