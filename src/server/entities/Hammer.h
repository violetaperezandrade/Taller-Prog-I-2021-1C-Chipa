#ifndef HAMMER_H
#define HAMMER_H

#include "../../common/Entity.h"

class Hammer : public Entity{
private:
    int usages;
public:
    Hammer(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Hammer();

};


#endif //HAMMER_H
