#include "CollisionManager.h"

#include <cmath>

#define PI 3.14159265

CollisionManager::CollisionManager(Character &character, std::vector<Entity> &vector, Logger& logger) :
    character(character),
    vector(vector),
    logger(logger)
{}

CollisionManager::~CollisionManager() {}

void CollisionManager::movePlatform(Entity &entity) {
    int speedX = entity.getSpeedX();
    int posX = entity.getPosX();

    entity.setPosX(posX + speedX);

    if(speedX > 0 && posX >= 742){
        entity.setPosX(86);
    }else if(speedX < 0 && posX <= 86){
        entity.setPosX(742);
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
        entity.setSpeedY(-2);
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

void CollisionManager::moveCharacter() {
    int speedX = character.getSpeedX();
    int speedY = character.getSpeedY();
    //double angle = getAngle(speedX,speedY);

    int map_width = 800;//config.get_map_width();
    int map_height = 600;//config.get_map_heigth();
    int x = character.getPosX() + speedX;
    int y = character.getPosY() + speedY;

    if (x < 0){
        x = 0;
    } else if (x > map_width){
        x = map_width;
    }

    if (y <= 0){
        y = 0;
        character.land();
        logger.debugMsg("Character has landed");
        character.setSpeedY(0);
    } else if (y > map_width){
        y = map_width;
    }
}