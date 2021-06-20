#ifndef PRINCESS_H
#define PRINCESS_H

#include "../../common/Entity.h"

class Princess : public Entity {
public:
    Princess(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Princess();
};

#endif //PRINCESS_H
