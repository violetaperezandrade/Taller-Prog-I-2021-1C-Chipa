#ifndef CHARACTER_H
#define CHARACTER_H

#include "../../common/Entity.h"
#include "Movement.h"
#include "../../common/Config.h"

class Character : public Entity{
private:
    Movement movement;
    char lastDirection;
    int lives;
    int points;

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

    void land();

    void attemptJump(Config& config);

    void attemptClimb(Config& config);

    void attemptGroundMovement(Config& config);

    bool isOnStairs();

    void setOnStairs(bool value);

    void setFalling();

    bool isGrounded();

    bool isClimbing();

    bool isTryingToClimb();

    bool isMidair();

    void updateStatus(Config& config);

    void disconnect();

    void reconnect();

    void loseLive();

    void addPoints(int i);

    int getLives();

    int getPoints();

    ~Character();
};


#endif
