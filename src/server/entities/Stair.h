#ifndef STAIR_H
#define STAIR_H

#include "../Entity.h"

class Stair : public Entity {
public:
    Stair(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Stair();

    char getState() override;
};

#endif //STAIR_H
