#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Entity.h"

class Character : public Entity{
private:
    int state;
public:
    Character(int posX, int posY, int width, int height, int speedX, int speedY);

    void jump();

    void land();

    void climb();

    bool isGrounded();

    bool isClimbing();

    ~Character();
};


#endif
