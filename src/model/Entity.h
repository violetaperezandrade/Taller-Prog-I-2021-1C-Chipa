#ifndef ENTITY_H
#define ENTITY_H

#include "Coordinate.h"
#include "Size.h"

class Entity {
private:
    Coordinate coordinate;
    Size size;

public:
    Entity();
    ~Entity();
};

#endif //ENTITY_H
