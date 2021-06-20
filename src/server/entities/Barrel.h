#ifndef BARREL_H
#define BARREL_H
#include "../../common/Entity.h"

class Barrel : public Entity {
public:
    Barrel(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Barrel();
};

#endif //BARREL_H
