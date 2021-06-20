#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "vector"
#include "../common/Entity.h"
#include "entities/Character.h"
#include "../common/Logger.h"

class CollisionManager {
private:
    std::vector<Character>& characters;
    std::vector<Entity>& vector;
    Logger& logger;
    void getEdgeInfo(int* cornerInfo, Entity& entity);
    void fixCharacterHitbox(int* edgeInfo);
    void undoCharacterHitbox(int* edgeInfo);
    bool checkHorizontalMatch(int* edgeInfoA, int* edgeInfoB);
    bool checkVerticalMatch(int* edgeInfoA, int* edgeInfoB);
    bool checkCollision(Entity& a, Entity& b);

    bool isPlayerMovementEntity(Entity& entity);
    void haltMovement(Entity& moving, Entity& obstacle, int* edgeInfo);

    void climb(int i);

public:
    CollisionManager(std::vector<Character>& character, std::vector<Entity>& vector, Logger& logger);

    void movePlatform(Entity &entity);

    bool moveBarrel(Entity &entity);

    bool moveEmber(Entity &entity);

    bool moveCharacter(int i);

    ~CollisionManager();
};

#endif //COLLISIONMANAGER_H
