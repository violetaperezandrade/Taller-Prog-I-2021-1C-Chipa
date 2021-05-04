#include "CollisionManager.h"

#include <cmath>

#define PI 3.14159265

CollisionManager::CollisionManager(int &character,
                                   std::vector<Entity> &vector) {}

CollisionManager::~CollisionManager() {}

void CollisionManager::move(Entity &entity) {

}

double CollisionManager::getAngle(int x, int y){
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
}

void CollisionManager::move(Character &character) {
    int speedX = character.getSpeedX();
    int speedY = character.getSpeedY();
    //double angle = getAngle(speedX,speedY);

    int map_width = config.get_map_width();
    int map_height = config.get_map_heigth();
    int x = character.getX() + speedX;
    int y = character.getY() + speedY;
    if (character.isMidair()){
        character.setSpeedY(speedY-config.getGravity())
    }

    if (x < 0){
        x = 0;
    } else if (x > map_width){
        x = map_width;
    }

    if (y < 0){
        y = 0;
        character.setLanding();
        character.setSpeedY(0);
    } else if (y > map_width){
        y = map_width;
    }
}