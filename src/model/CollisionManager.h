#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "vector"
#include "Entity.h"
#include "Character.h"

class CollisionManager {
private:
    Character& character;
    std::vector<Entity>& vector;
    void move_midair(Character& character);
    void move_left(Character& character);
    void move_right(Character& character);

public:
    CollisionManager(Character& character, std::vector<Entity>& vector);
    ~CollisionManager();
    void move(Entity& entity);
    void move(Character& character);
};

#endif //COLLISIONMANAGER_H
