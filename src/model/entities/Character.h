#ifndef CHARACTER_H
#define CHARACTER_H

#include "../Entity.h"
#include "Movement.h"
#include "../../controller/Config.h"

class Character : public Entity{
private:
    char state;
    Movement movement;
    char lastDirection;

public:
    Character(int posX, int posY, int width, int height, int speedX, int speedY);

    void startMovingLeft();

    void startMovingRight();

    void startMovingUp();

    void startMovingDown();

    void startJumping();

    void stopMovingLeft();

    void stopMovingRight();

    void stopMovingUp();

    void stopMovingDown();

    void stopJumping();

    void jump();

    void land();

    void climb();

    bool isGrounded();

    bool isClimbing();

    bool isMidair();

    void updateStatus(Config& config);

    char getState() override;

    ~Character();
};


#endif
