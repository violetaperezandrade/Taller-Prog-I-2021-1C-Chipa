#ifndef PLATFORM_H
#define PLATFORM_H

#include "../../common/Entity.h"

class Platform : public Entity {
public:
    Platform(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Platform();
};

#endif //PLATFORM_H
