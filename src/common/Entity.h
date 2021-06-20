#ifndef ENTITY_H
#define ENTITY_H
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>

class Entity {
protected:
    char type;
    int posX;
    int posY;
    int width;
    int height;
    int speedX;
    int speedY;
    char state;
    char permanency;

    //static const int ENTITYSPEED = 5;

public:
    Entity(char type, int x, int y, int width, int height);

    Entity(char type, int posX, int posY, int width, int height,
           int speedX, int speedY, char state, char permanency);

    void setPosY(int i);

    void setPosX(int i);

    void setSpeedX(int i);

    void setSpeedY(int i);

    int getPosY();

    int getPosX();

    int getSpeedX();

    int getSpeedY();

    int getWidth();

    int getHeight();

    char getType();

    char getPermanency();

    void setPermanency(char c);

    char getState(); // REVISAR le pongo a todos un state?

    //virtual ~Entity();
    ~Entity();

};

#endif //ENTITY_H
