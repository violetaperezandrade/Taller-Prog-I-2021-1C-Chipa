#include "CollisionManager.h"

#include <cmath>

#define PI 3.14159265
#define PLATFORM_HEIGHT 20

#define LEFT 0
#define RIGHT 1
#define TOP 2
#define BOTTOM 3

#define CHARACTER_CODE 'C'

#define CHARACTER_SIDE_PADDING 16;
#define CHARACTER_TOP_PADDING 9;

CollisionManager::CollisionManager(std::vector<Character>& character, std::vector<Entity> &vector, Logger& logger) :
    characters(character),
    vector(vector),
    logger(logger)
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
    edgeInfo[RIGHT] += CHARACTER_SIDE_PADDING;
    edgeInfo[TOP] += CHARACTER_TOP_PADDING;
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

    bool verticalMatch = false;
    bool horizontalMatch = false;

    if((edgeInfoA[LEFT] >= edgeInfoB[LEFT]) && (edgeInfoA[LEFT] <= edgeInfoB[RIGHT])){
        horizontalMatch = true;
    }
    if((edgeInfoA[RIGHT] >= edgeInfoB[LEFT]) && (edgeInfoA[RIGHT] <= edgeInfoB[RIGHT])){
        horizontalMatch = true;
    }
    if((edgeInfoB[LEFT] >= edgeInfoA[LEFT]) && (edgeInfoB[LEFT] <= edgeInfoA[RIGHT])){
        horizontalMatch = true;
    }
    if((edgeInfoB[RIGHT] >= edgeInfoA[LEFT]) && (edgeInfoB[RIGHT] <= edgeInfoA[RIGHT])){
        horizontalMatch = true;
    }
    if((edgeInfoA[TOP] >= edgeInfoB[TOP]) && (edgeInfoA[TOP] <= edgeInfoB[BOTTOM])){
        verticalMatch = true;
    }
    if((edgeInfoA[BOTTOM] >= edgeInfoB[TOP]) && (edgeInfoA[BOTTOM] <= edgeInfoB[BOTTOM])){
        verticalMatch = true;
    }
    if((edgeInfoB[TOP] >= edgeInfoA[TOP]) && (edgeInfoB[TOP] <= edgeInfoA[BOTTOM])){
        verticalMatch = true;
    }
    if((edgeInfoB[BOTTOM] >= edgeInfoA[TOP]) && (edgeInfoB[BOTTOM] <= edgeInfoA[BOTTOM])){
        verticalMatch = true;
    }
    return (verticalMatch && horizontalMatch);
}

void CollisionManager::moveCharacter(int i) {
    int mapWidth = 800;//config.get_map_width();
    int mapHeight = 600;//config.get_map_heigth();
    int height = characters[i].getHeight();
    int width = characters[i].getWidth();

    int edgeInfo[4];
    getEdgeInfo(edgeInfo, characters[i]);

    if (edgeInfo[LEFT] < 0){
        edgeInfo[LEFT] = 0;
        edgeInfo[RIGHT] = width;
    } else if (edgeInfo[RIGHT] > mapWidth){
        edgeInfo[LEFT] = mapWidth-width;
        edgeInfo[RIGHT] = mapWidth;
    }

    if (edgeInfo[BOTTOM] >= 600-(PLATFORM_HEIGHT)){
        edgeInfo[BOTTOM] = 600-(PLATFORM_HEIGHT);
        edgeInfo[TOP] = 600-(height+PLATFORM_HEIGHT);
        characters[i].land();
        logger.debugMsg("Character has landed", __FILE__, __LINE__);
    } else if (edgeInfo[TOP] <= 0){
        edgeInfo[TOP] = 0;
        edgeInfo[BOTTOM] = height;
    }


    for (int j = 0; j < vector.size(); j++){
        if (checkCollision(characters[i], vector[j])){
            //aca iria la colision
        }
    }

    characters[i].setPosX(edgeInfo[LEFT]);
    characters[i].setPosY(edgeInfo[RIGHT]);
}