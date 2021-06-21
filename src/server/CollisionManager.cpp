#include "CollisionManager.h"

#include <cmath>
#include <stdlib.h>

#define PI 3.14159265
#define PLATFORM_HEIGHT 20

#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3

#define BARREL_CODE 'B'
#define CHARACTER_CODE 'C'
#define EMBER_CODE 'E'
#define FIRE_CODE 'F'
#define FLAME_CODE 'f'
#define MONKEY_CODE 'M'
#define PLATFORM_CODE 'P'
#define PRINCESS_CODE 'p'
#define STAIR_CODE 'S'

#define CHARACTER_SIDE_PADDING 16;
#define CHARACTER_TOP_PADDING 9;

CollisionManager::CollisionManager(std::vector<Character>& character, std::vector<Entity> &vector, Logger& logger, Config& config) :
    characters(character),
    vector(vector),
    logger(logger),
    config(config)
{}

CollisionManager::~CollisionManager() {}

void CollisionManager::movePlatform(Entity &entity) {
    int speedX = entity.getSpeedX();
    int posX = entity.getPosX();

    entity.setPosX(posX + speedX);

    if(speedX > 0 && posX >= 680){
        entity.setPosX(60);
    }else if(speedX < 0 && posX <= 60){
        entity.setPosX(680);
    }
}

bool CollisionManager::moveBarrel(Entity &entity) {
    int posY = entity.getPosY();
    int speedY = entity.getSpeedY();

    entity.setPosY(posY + speedY);

    if(posY >= 750){
        return true;
    }
    return false;
}

bool CollisionManager::moveEmber(Entity &entity) {
    int posY = entity.getPosY();
    int speedY = entity.getSpeedY();

    entity.setPosY(posY + speedY);

    if(posY <= 241){
        entity.setSpeedY(12);
        return false;
    }else if(posY >= 565){
        return true;
    }
    return false;
}

/*double CollisionManager::getAngle(int x, int y){
    if (x == 0){
        if (y > 0){
            return 90;
        } else if (y < 0){
            return 270;
        } else {
            return 0; // Error porque me mandaron 0 y 0?
        }
    }

    double angle = atan(y/x) * 180 / PI;
    if (x < 0) {
        angle += 180;
    } else if (y < 0){
        angle+= 360;
    }
    return angle;
}*/

void CollisionManager::getEdgeInfo(int* edgeInfo, Entity& entity){
    int speedX = entity.getSpeedX();
    if (speedX){
        logger.superDebugMsg("speedX:" + std::to_string(speedX), __FILE__, __LINE__);
    }
    int speedY = entity.getSpeedY();

    int x = entity.getPosX() + speedX;
    int y = entity.getPosY() + speedY;
    int height = entity.getHeight();
    int width = entity.getWidth();

    edgeInfo[LEFT] = x;
    edgeInfo[RIGHT] = x+width;
    edgeInfo[TOP] = y;
    edgeInfo[BOTTOM] = y+height;
}

void CollisionManager::fixCharacterHitbox(int* edgeInfo){
    edgeInfo[LEFT] += CHARACTER_SIDE_PADDING;
    edgeInfo[RIGHT] -= CHARACTER_SIDE_PADDING;
    edgeInfo[TOP] += CHARACTER_TOP_PADDING;
}

void CollisionManager::undoCharacterHitbox(int* edgeInfo){
    edgeInfo[LEFT] -= CHARACTER_SIDE_PADDING;
    edgeInfo[RIGHT] += CHARACTER_SIDE_PADDING;
    edgeInfo[TOP] -= CHARACTER_TOP_PADDING;
}

bool CollisionManager::checkHorizontalMatch(int* edgeInfoA, int* edgeInfoB){
    if((edgeInfoA[LEFT] >= edgeInfoB[LEFT]) && (edgeInfoA[LEFT] <= edgeInfoB[RIGHT])){
        return true;
    }
    if((edgeInfoA[RIGHT] >= edgeInfoB[LEFT]) && (edgeInfoA[RIGHT] <= edgeInfoB[RIGHT])){
        return true;
    }
    if((edgeInfoB[LEFT] >= edgeInfoA[LEFT]) && (edgeInfoB[LEFT] <= edgeInfoA[RIGHT])){
        return true;
    }
    if((edgeInfoB[RIGHT] >= edgeInfoA[LEFT]) && (edgeInfoB[RIGHT] <= edgeInfoA[RIGHT])){
        return true;
    }
    return false;
}

bool CollisionManager::checkVerticalMatch(int* edgeInfoA, int* edgeInfoB){
    if((edgeInfoA[TOP] >= edgeInfoB[TOP]) && (edgeInfoA[TOP] <= edgeInfoB[BOTTOM])){
        return true;
    }
    if((edgeInfoA[BOTTOM] >= edgeInfoB[TOP]) && (edgeInfoA[BOTTOM] <= edgeInfoB[BOTTOM])){
        return true;
    }
    if((edgeInfoB[TOP] >= edgeInfoA[TOP]) && (edgeInfoB[TOP] <= edgeInfoA[BOTTOM])){
        return true;
    }
    if((edgeInfoB[BOTTOM] >= edgeInfoA[TOP]) && (edgeInfoB[BOTTOM] <= edgeInfoA[BOTTOM])){
        return true;
    }
    return false;
}

bool CollisionManager::checkCollision(Entity &a, Entity &b) {
    int edgeInfoA[4], edgeInfoB[4];
    getEdgeInfo(edgeInfoA, a);
    getEdgeInfo(edgeInfoB, b);
    if (a.getType() == CHARACTER_CODE){
        fixCharacterHitbox(edgeInfoA);
    }
    if (b.getType() == CHARACTER_CODE){
        fixCharacterHitbox(edgeInfoB);
    }

    bool verticalMatch = checkHorizontalMatch(edgeInfoA, edgeInfoB);
    bool horizontalMatch = checkVerticalMatch(edgeInfoA, edgeInfoB);
    if (verticalMatch && horizontalMatch){
        std::cout << "First entity edges: Left: " << edgeInfoA[0] << ", Right: " << edgeInfoA[1] << ", Top: " << edgeInfoA[2] << ", Bottom: " << edgeInfoA[3] << '\n';
        std::cout << "Second entity edges: Left: " << edgeInfoB[0] << ", Right: " << edgeInfoB[1] << ", Top: " << edgeInfoB[2] << ", Bottom: " << edgeInfoB[3] << '\n';
    }
    return (verticalMatch && horizontalMatch);
}

bool CollisionManager::isPlayerMovementEntity(Entity& entity) {
    char type = entity.getType();
    if (type == BARREL_CODE || type == EMBER_CODE || type == FIRE_CODE ||
        type == FLAME_CODE || type == PLATFORM_CODE || type == PRINCESS_CODE){
        return true;
    }
    return false;
}

void CollisionManager::haltMovement(Entity &moving, Entity &obstacle, int* edgeInfoA) {
    int speedX = moving.getSpeedX();
    int speedY = moving.getSpeedY();
    int deltaX = 0, deltaY = 0;

    int edgeInfoB[4];
    getEdgeInfo(edgeInfoB, obstacle);

    if (speedX > 0){
        deltaX = 1 + edgeInfoA[RIGHT] - edgeInfoB[LEFT];
    } else if (speedX < 0){
        deltaX = -1 + edgeInfoA[LEFT] - edgeInfoB[RIGHT];
    }

    if (speedY > 0){
        deltaY = 1 + edgeInfoA[BOTTOM] - edgeInfoB[TOP];
    } else if (speedY < 0){
        deltaY = -1 + edgeInfoA[TOP] - edgeInfoB[BOTTOM];
    }

    if (abs(deltaX) > abs(deltaY)){
        edgeInfoA[LEFT] -= deltaX;
        edgeInfoA[RIGHT] -= deltaX;
        std::cout << "Halt Movement with deltaX: " << deltaX <<'\n';
    } else {
        edgeInfoA[TOP] -= deltaY;
        edgeInfoA[BOTTOM] -= deltaY;
        std::cout << "Halt Movement with deltaY: " << deltaX <<'\n';
    }
}

void CollisionManager::climb(int i) {
    bool stairCollision = false;

    for (int j = 0; j < vector.size(); j++){
        if (checkCollision(characters[i], vector[j])){
            char type = vector[j].getType();
            if(type == BARREL_CODE || type == EMBER_CODE || type == FIRE_CODE ||
               type == FLAME_CODE){
                //maybe halt movement
                //hit
            } else if(type == STAIR_CODE){
                stairCollision = true;
            }
        }
    }

    if (stairCollision){
        characters[i].setOnStairs(true);
        characters[i].updateStatus(config);
        int edgeInfo[4];
        getEdgeInfo(edgeInfo, characters[i]);
        characters[i].setPosX(edgeInfo[LEFT]);
        characters[i].setPosY(edgeInfo[TOP]);
    }
}

bool CollisionManager::moveCharacter(int i) {
    characters[i].setOnStairs(false);
    if (characters[i].isTryingToClimb()){
        climb(i);
        return false;
    }
    if (characters[i].getSpeedX() == 0 && characters[i].getSpeedY() == 0){
        return false;
    }
    bool switchLevel = false;
    int mapWidth = 800;//config.get_map_width();
    int mapHeight = 600;//config.get_map_heigth();
    int height = characters[i].getHeight();
    int width = characters[i].getWidth();

    int edgeInfo[4];
    getEdgeInfo(edgeInfo, characters[i]);
    std::cout << "\nStarting info: PosX: " << characters[i].getPosX() << ",  PosY: " << characters[i].getPosY() << ",  SpeedX: " << characters[i].getSpeedX() << ",  SpeedY: " << characters[i].getSpeedY() << ",  Width: " << characters[i].getWidth() << ",  Height: " << characters[i].getHeight() << '\n';
    std::cout << "Left: " << edgeInfo[0] << ", Right: " << edgeInfo[1] << ", Top: " << edgeInfo[2] << ", Bottom: " << edgeInfo[3] << '\n';

    if (edgeInfo[LEFT] < 0){
        edgeInfo[LEFT] = 0;
        edgeInfo[RIGHT] = width;
    } else if (edgeInfo[RIGHT] > mapWidth){
        edgeInfo[LEFT] = mapWidth-width;
        edgeInfo[RIGHT] = mapWidth;
    }

    if (edgeInfo[BOTTOM] >= mapHeight-(PLATFORM_HEIGHT)){
        edgeInfo[BOTTOM] = mapHeight-(PLATFORM_HEIGHT)-1;
        edgeInfo[TOP] = mapHeight-(height+PLATFORM_HEIGHT)-1;
        characters[i].land();
        logger.debugMsg("Character has landed", __FILE__, __LINE__);
    } else if (edgeInfo[TOP] <= 0){
        edgeInfo[TOP] = 0;
        edgeInfo[BOTTOM] = height;
    }

    //std::cout << "After colliding with edge\n";
    //std::cout << "Left: " << edgeInfo[0] << ", Right: " << edgeInfo[1] << ", Top: " << edgeInfo[2] << ", Bottom: " << edgeInfo[3] << '\n';
    int previousY = edgeInfo[TOP];

    fixCharacterHitbox(edgeInfo);

    for (int j = 0; j < vector.size(); j++){
        if (isPlayerMovementEntity(vector[j]) && checkCollision(characters[i], vector[j])){
            char type = vector[j].getType();
            if(type == BARREL_CODE || type == EMBER_CODE || type == FIRE_CODE ||
               type == FLAME_CODE){
                //maybe halt movement
                //hit
            } else if(type == PLATFORM_CODE){
                haltMovement(characters[i], vector[j], edgeInfo);
                if (previousY > edgeInfo[TOP]){
                    characters[i].land();
                    std::cout << "----Landing\n";
                }
                std::cout << "After colliding with platform\n";
                std::cout << "Left: " << edgeInfo[0] << ", Right: " << edgeInfo[1] << ", Top: " << edgeInfo[2] << ", Bottom: " << edgeInfo[3] << '\n';
            } else if(type == PRINCESS_CODE){
                switchLevel = true;
            }
        }
    }
    undoCharacterHitbox(edgeInfo);
    characters[i].setPosX(edgeInfo[LEFT]);
    characters[i].setPosY(edgeInfo[TOP]);
    return switchLevel;
}