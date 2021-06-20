#ifndef EMBER_H
#define EMBER_H

#include "../../common/Entity.h"

class Ember : public Entity {
public:
    Ember(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Ember();
};

#endif //EMBER_H
