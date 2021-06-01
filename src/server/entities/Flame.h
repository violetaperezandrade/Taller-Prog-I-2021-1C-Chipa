#ifndef FLAME_H
#define FLAME_H

#include "../Entity.h"

class Flame : public Entity {
public:
    Flame(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Flame();

    char getState() override;
};

#endif //FLAME_H
