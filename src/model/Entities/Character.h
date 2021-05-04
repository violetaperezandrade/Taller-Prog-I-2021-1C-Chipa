#ifndef DONKEYKONG_CHARACTER_H
#define DONKEYKONG_CHARACTER_H

#include "../Entity.h"

class Character : public Entity{
private:
    int state;
public:
    Character(int posX, int posY, int width, int height, int speedX, int speedY);

    void jump();

    void land();

    bool isJumping();

    ~Character();
};


#endif
