#include "Monkey.h"

#define MONKEY_CODE 'M'
#define MONKEY_STATE '0'

Monkey::Monkey(int posX, int posY, int width, int height, int speedX, int speedY) :
        Entity(MONKEY_CODE, posX, posY, width, height, speedX, speedY, MONKEY_STATE, 'P')
{}

Monkey::~Monkey(){}
