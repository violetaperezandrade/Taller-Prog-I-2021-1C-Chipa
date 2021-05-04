#ifndef BARREL_H
#define BARREL_H
#include "Entity.h"

class Barrel : public Entity {
protected:
    int speedX;
    int speedY;
public:
    Barrel(int x, int y);
    ~Barrel();
    void move();
};


#endif //BARREL_H
