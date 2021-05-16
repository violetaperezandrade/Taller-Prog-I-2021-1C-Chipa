#ifndef EMBER_H
#define EMBER_H

#include "../Entity.h"

class Ember : public Entity {
public:
    Ember(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Ember();

    char getState() override;
};

#endif //EMBER_H
