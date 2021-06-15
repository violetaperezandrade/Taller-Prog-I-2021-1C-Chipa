#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "vector"
#include "Entity.h"
#include "entities/Character.h"
#include "../common/Logger.h"

class CollisionManager {
private:
    std::vector<Character>& characters;
    std::vector<Entity>& vector;
    Logger& logger;
    void getEdgeInfo(int* cornerInfo, Entity& entity);
    void fixCharacterHitbox(int* edgeInfo);
    bool checkCollision(Entity& a, Entity& b);

    bool isPlayerMovementEntity(Entity& entity);

public:
    CollisionManager(std::vector<Character>& character, std::vector<Entity>& vector, Logger& logger);

    void movePlatform(Entity &entity);

    bool moveBarrel(Entity &entity);

    bool moveEmber(Entity &entity);

    bool moveCharacter(int i);

    ~CollisionManager();
};

#endif //COLLISIONMANAGER_H
