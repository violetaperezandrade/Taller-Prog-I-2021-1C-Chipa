#ifndef ENTITY_H
#define ENTITY_H

#include "ScreenConfig.h"

class Entity {
protected:
    int posX;
    int posY;
    int width;
    int height;
    int speedX;
    int speedY;

    static const int ENTITYSPEED = 5;


public:
    Entity(int x, int y, int width, int height);

    Entity(int posX, int posY, int width, int height, int speedX, int speedY);

    void setPosY(int& i);

    void setPosX(int& i);

    void setSpeedX(int& i);

    void setSpeedY(int& i);

    int getPosY();

    int getPosX();

    int getSpeedX();

    int getSpeedY();

    virtual ~Entity();

    void handleEvent(SDL_Event& e);
    void move();
    void render();
};

#endif //ENTITY_H
