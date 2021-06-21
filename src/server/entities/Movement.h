#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
private:
    char state;
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    bool jumping;
    bool onStairs;

public:
    Movement();
    ~Movement();
    
    void setMovingLeft(bool value);
    void setMovingRight(bool value);
    void setMovingUp(bool value);
    void setMovingDown(bool value);
    void setJumping(bool value);
    /*void setGrounded(bool value);
    void setMidair(bool value);
    void setClimbing(bool value);*/
    bool attemptJump();
    bool attemptClimb();
    void land();
    void setOnStairs(bool value);
    void setFalling();

    bool isMidair();
    bool isClimbing();
    bool isGrounded();
    //bool isOnStairs();
    bool isTryingToClimb();

    bool shouldMoveLeft();
    bool shouldMoveRight();
    bool isMovingLeft();
    bool isMovingRight();
    bool shouldMoveUp();
    bool shouldMoveDown();
    /*bool shouldJump();
    bool shouldFall();
    bool shouldClimb();*/

};

#endif //MOVEMENT_H
