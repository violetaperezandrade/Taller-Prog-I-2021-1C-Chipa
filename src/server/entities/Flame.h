#ifndef FLAME_H
#define FLAME_H

#include "../../common/Entity.h"

class Flame : public Entity {
public:
    Flame(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Flame();
};

#endif //FLAME_H
