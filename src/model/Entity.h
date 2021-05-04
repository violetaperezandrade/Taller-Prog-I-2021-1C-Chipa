#ifndef ENTITY_H
#define ENTITY_H

#include "Coordinate.h"
#include "Size.h"

class Entity {
protected:
    int x;
    int y;
    int width;
    int height;
    int speedX;
    int speedY;

public:
    Entity();
    Entity(int x, int y, int width, int height);
    ~Entity();
};

#endif //ENTITY_H
