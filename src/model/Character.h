#ifndef DONKEYKONG_CHARACTER_H
#define DONKEYKONG_CHARACTER_H

class Character {
private:
    int pos_x;
    int pos_y;
    int vel_x;
    int vel_y;
    int state;
public:
    Character();

    void jump();

    void runLeft();

    void runRight();

    void moveLeft();

    void moveRight();

    ~Character();

};


#endif
