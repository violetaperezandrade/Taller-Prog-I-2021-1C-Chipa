#include "CollisionManager.h"

#include <cmath>

#define PI 3.14159265
#define PLATFORM_HEIGHT 20

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

void CollisionManager::moveCharacter() {
    int speedX = character.getSpeedX();
    if (speedX){
        logger.superDebugMsg("speedX:" + std::to_string(speedX));
    }
    int speedY = character.getSpeedY();
    //double angle = getAngle(speedX,speedY);

    int map_width = 800;//config.get_map_width();
    int map_height = 600;//config.get_map_heigth();
    int x = character.getPosX() + speedX;
    int y = character.getPosY() + speedY;
    int height = character.getHeight();
    int width = character.getWidth();

    if (x < 0){
        x = 0;
    } else if (x > map_width-width){
        x = map_width-width;
    }

    if (y >= 600-(height+PLATFORM_HEIGHT)){
        y = 600-(height+PLATFORM_HEIGHT);
        character.land();
        logger.debugMsg("Character has landed");
    } else if (y <= 0){
        y = 0;
    }
    character.setPosX(x);
    character.setPosY(y);
}