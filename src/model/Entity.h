#ifndef ENTITY_H
#define ENTITY_H

#include "Coordinate.h"
#include "Size.h"

class Entity {
protected:
    Coordinate coordinate;
    Size size;

public:
    Entity();
    Entity(int x, int y);
    ~Entity();
};

#endif //ENTITY_H
