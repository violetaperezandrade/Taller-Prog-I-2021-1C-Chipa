#include "Ember.h"

#define EMBER_CODE "E"

Ember::Ember(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(EMBER_CODE, posX, posY, width, height, speedX, speedY)
{}

Ember::~Ember(){}