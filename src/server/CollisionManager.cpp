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
#define HAMMER_CODE 'H'

#define CHARACTER_SIDE_PADDING 16
#define CHARACTER_TOP_PADDING 9

#define CHARACTER_FOOTING_PADDING 16

#define MAP_WIDTH 800
#define MAP_HEIGHT 600

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

void CollisionManager::getStillEdgeInfo(int* edgeInfo, Entity& entity){
    edgeInfo[LEFT] = entity.getPosX();
    edgeInfo[RIGHT] = edgeInfo[LEFT]+entity.getWidth();
    edgeInfo[TOP] = entity.getPosY();
    edgeInfo[BOTTOM] = edgeInfo[TOP]+entity.getHeight();
}

void CollisionManager::getFloorEdgeInfo(int* edgeInfo, Entity& entity){
    edgeInfo[LEFT] = entity.getPosX() + CHARACTER_FOOTING_PADDING;
    edgeInfo[RIGHT] = edgeInfo[LEFT]+entity.getWidth() - CHARACTER_FOOTING_PADDING;
    edgeInfo[TOP] = entity.getPosY()+entity.getHeight()+1;
    edgeInfo[BOTTOM] = edgeInfo[TOP];
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

    bool horizontalMatch = checkHorizontalMatch(edgeInfoA, edgeInfoB);
    bool verticalMatch = checkVerticalMatch(edgeInfoA, edgeInfoB);
    return (verticalMatch && horizontalMatch);
}

bool CollisionManager::checkStillCollision(Entity &a, Entity &b) {
    int edgeInfoA[4], edgeInfoB[4];
    getStillEdgeInfo(edgeInfoA, a);
    getStillEdgeInfo(edgeInfoB, b);
    if (a.getType() == CHARACTER_CODE){
        fixCharacterHitbox(edgeInfoA);
    }
    if (b.getType() == CHARACTER_CODE){
        fixCharacterHitbox(edgeInfoB);
    }

    bool horizontalMatch = checkHorizontalMatch(edgeInfoA, edgeInfoB);
    bool verticalMatch = checkVerticalMatch(edgeInfoA, edgeInfoB);
    return (verticalMatch && horizontalMatch);
}

bool CollisionManager::checkGroundedCollision(Entity &a, Entity &b) {
    int edgeInfoA[4], edgeInfoB[4];
    getFloorEdgeInfo(edgeInfoA, a);
    getStillEdgeInfo(edgeInfoB, b);

    bool horizontalMatch = checkHorizontalMatch(edgeInfoA, edgeInfoB);
    bool verticalMatch = checkVerticalMatch(edgeInfoA, edgeInfoB);
    return (verticalMatch && horizontalMatch);
}

bool CollisionManager::isPlayerMovementEntity(Entity& entity) {
    char type = entity.getType();
    if (type == BARREL_CODE || type == EMBER_CODE || type == FIRE_CODE ||
        type == FLAME_CODE || type == PLATFORM_CODE || type == PRINCESS_CODE ||
        type == HAMMER_CODE){
        return true;
    }
    return false;
}

void CollisionManager::haltMovement(Entity &moving, Entity &obstacle, int* edgeInfoA) {
    int speedX = moving.getSpeedX();
    int speedY = moving.getSpeedY();
    int deltaX = 0, deltaY = 0;
    bool moveX;

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

    //moveX = abs(deltaX) > abs(deltaY);
    moveX = (deltaY == 0) || (deltaX != 0 && abs(deltaX) < abs(deltaY));
    if (moveX){
        edgeInfoA[LEFT] -= deltaX;
        edgeInfoA[RIGHT] -= deltaX;
    } else {
        edgeInfoA[TOP] -= deltaY;
        edgeInfoA[BOTTOM] -= deltaY;
    }
}

bool CollisionManager::moveCharacter(int i, int& playersWhoFinished) {
    /*if (characters[i].isTryingToClimb()){
        climb(i);
        return false;
    }*/
    if (characters[i].getSpeedX() == 0 && characters[i].getSpeedY() == 0){
        return false;
    }
    bool switchLevel = false;
    int mapWidth = 800;//config.get_map_width();
    int mapHeight = 600;//config.get_map_heigth();
    int height = characters[i].getHeight();
    int width = characters[i].getWidth();
    bool gotHit = false;

    int edgeInfo[4];
    getEdgeInfo(edgeInfo, characters[i]);

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

    int previousY = edgeInfo[TOP];

    fixCharacterHitbox(edgeInfo);

    for (int j = 0; j < vector.size(); j++){
        if (isPlayerMovementEntity(vector[j]) && checkCollision(characters[i], vector[j])){
            char type = vector[j].getType();
            if(type == BARREL_CODE || type == EMBER_CODE || type == FIRE_CODE ||
               type == FLAME_CODE){
                if(characters[i].hasHammer()){
                    characters[i].useHammer();
                    vector.erase(vector.begin()+j);
                    j--;
                    logger.infoMsg("Martilleo un enemigo", __FILE__, __LINE__);
                    if(type == BARREL_CODE){
                        characters[i].addPoints(500);
                    } else {
                        characters[i].addPoints(1000);
                    }
                } else if (!characters[i].isDead()){
                    characters[i].loseLive();
                    if(!characters[i].isInvincible()) gotHit = true;
                }
            } else if(type == PLATFORM_CODE && !characters[i].isClimbing()){
                haltMovement(characters[i], vector[j], edgeInfo);
                if (previousY > edgeInfo[TOP]){
                    characters[i].land();
                }
            } else if(type == PRINCESS_CODE){
                gotHit = true;
                switchLevel = true;
                characters[i].setPosX(360);
                characters[i].setPosY( 79);
                playersWhoFinished++;
                characters[i].addPoints(2000 - playersWhoFinished * 500);
            } else if(type == HAMMER_CODE){
                vector.erase(vector.begin()+j);
                j--;
                characters[i].pickUpHammer();
                logger.infoMsg("Agarra martillo", __FILE__, __LINE__);
            }
        }
    }
    if (!gotHit){
        undoCharacterHitbox(edgeInfo);
        characters[i].setPosX(edgeInfo[LEFT]);
        characters[i].setPosY(edgeInfo[TOP]);
    }
    return switchLevel;
}

void CollisionManager::updateCollisionStatus() {
    for (int i = 0; i < characters.size(); i++){
        int edgeInfo[4];
        getEdgeInfo(edgeInfo, characters[i]);
        bool grounded = (edgeInfo[BOTTOM] >= MAP_HEIGHT-(PLATFORM_HEIGHT)-1);
        bool onStair = false;
        bool aboveStair = false;
        for (int j = 0; j < vector.size(); j++){
            char type = vector[j].getType();
            if(type == STAIR_CODE){
                if (checkStillCollision(characters[i], vector[j])){
                    onStair = true;
                }
                if (checkGroundedCollision(characters[i], vector[j])){
                    aboveStair = true;
                }
            } else if(type == PLATFORM_CODE){
                if (checkGroundedCollision(characters[i], vector[j])){
                    grounded = true;
                }
            }
        }
        characters[i].setOnStairs(onStair || aboveStair);
        if (!grounded && !onStair){
            characters[i].setFalling();
        }
    }
}

bool CollisionManager::moveBarrel(Entity &barrel, int& characterLeft) {
    int posX = barrel.getPosX();
    int posY = barrel.getPosY();
    int speedX = barrel.getSpeedX();
    int speedY = barrel.getSpeedY();
    barrel.setSpeedY(speedY + config.getGravity());
    bool hitAnything = false;
    int edgeInfo[4];
    getEdgeInfo(edgeInfo, barrel);

    for(int i = 0; i < vector.size() && !hitAnything; i++){
        if (checkCollision(barrel,vector[i])){
            char type = vector[i].getType();
            if (type == PLATFORM_CODE){
                haltMovement(barrel, vector[i], edgeInfo);
                barrel.setSpeedY(0);
                if (speedX == 0){
                    barrel.setSpeedX(4);
                }
                if (speedY > 4){
                    hitAnything = true;
                    if (speedX <= 0) {
                        barrel.setSpeedX(4);
                    } else {
                        barrel.setSpeedX(-4);
                    }
                }
            }
        }
    }
    for (int i = 0; i < characters.size(); i++){
        if(checkCollision(barrel, characters[i]) && !characters[i].isDead()){
            if(characters[i].hasHammer()){
                characters[i].useHammer();
                logger.infoMsg("Martilleo un enemigo", __FILE__, __LINE__);
                characters[i].addPoints(500);
            } else {
                characters[i].loseLive();
                if (characters[i].isDead()) characterLeft--;
            }
            return true;
        }
    }
    barrel.setPosX(edgeInfo[LEFT]+barrel.getSpeedX());
    barrel.setPosY(edgeInfo[TOP]+barrel.getSpeedY());

    if(edgeInfo[TOP] >= 750){
        return true;
    }
    return false;
}