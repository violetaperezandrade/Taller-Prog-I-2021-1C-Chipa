#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "vector"
#include "Entity.h"
#include "entities/Character.h"
#include "../common/Logger.h"

class CollisionManager {
private:
    Character& character;
    std::vector<Entity>& vector;
    Logger& logger;

public:
    CollisionManager(Character& character, std::vector<Entity>& vector, Logger& logger);

    void movePlatform(Entity &entity);

    bool moveBarrel(Entity &entity);

    bool moveEmber(Entity &entity);

    void moveCharacter();

    ~CollisionManager();
};

#endif //COLLISIONMANAGER_H
