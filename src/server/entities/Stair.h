#ifndef STAIR_H
#define STAIR_H

#include "../../common/Entity.h"

class Stair : public Entity {
public:
    Stair(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Stair();
};

#endif //STAIR_H
