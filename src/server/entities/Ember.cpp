#include "Ember.h"

#define EMBER_CODE 'E'
#define EMBER_STATE '0'

Ember::Ember(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(EMBER_CODE, posX, posY, width, height, speedX, speedY,'T')
{}

Ember::~Ember(){}

char Ember::getState() {
    return EMBER_STATE;
}