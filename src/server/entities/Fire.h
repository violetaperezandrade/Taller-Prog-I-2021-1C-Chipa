#ifndef FIRE_H
#define FIRE_H

#include "../../common/Entity.h"

class Fire : public Entity {
public:
    Fire(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Fire();
};

#endif //FIRE_H
