#ifndef MOVEMENT_H
#define MOVEMENT_H

class Movement {
private:
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    bool jumping;
    bool midair;
    bool onStairs;

public:
    Movement();
    ~Movement();
    
    void setMovingLeft(bool value);
    void setMovingRight(bool value);
    void setMovingUp(bool value);
    void setMovingDown(bool value);
    void setJumping(bool value);
    void setMidair(bool value);
    void setOnStairs(bool value);

    bool shouldMoveLeft();
    bool shouldMoveRight();
    bool shouldMoveUp();
    bool shouldMoveDown();
    bool shouldJump();
    bool shouldFall();
    bool shouldGetOnStairs();

};

#endif //MOVEMENT_H
