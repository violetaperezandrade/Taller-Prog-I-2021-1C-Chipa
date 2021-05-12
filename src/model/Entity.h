#ifndef ENTITY_H
#define ENTITY_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "ScreenConfig.h"

class Entity {
protected:
    char type;
    int posX;
    int posY;
    int width;
    int height;
    int speedX;
    int speedY;

    static const int ENTITYSPEED = 5;

public:
    Entity(char type, int x, int y, int width, int height);

    Entity(char type, int posX, int posY,
           int width, int height, int speedX, int speedY);

    void setPosY(int& i);

    void setPosX(int& i);

    void setSpeedX(int& i);

    void setSpeedY(int& i);

    int getPosY();

    int getPosX();

    int getSpeedX();

    int getSpeedY();

    int getWidth();

    int getHeight();

    char getType();

    //virtual ~Entity();
    ~Entity();
    void handleEvent(SDL_Event& e);
    void move();
    void render();
};

#endif //ENTITY_H
