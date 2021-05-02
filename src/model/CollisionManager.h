#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "vector"
#include "Entity.h"
#include "Character.h"

class CollisionManager {
private:
    Character& character;
    std::vector<Entity>& vector;

public:
    CollisionManager(Character& character, std::vector<Entity>& vector);
    ~CollisionManager();
    void move(Entity& entity);
};

#endif //COLLISIONMANAGER_H
