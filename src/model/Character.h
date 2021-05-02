#ifndef DONKEYKONG_CHARACTER_H
#define DONKEYKONG_CHARACTER_H

class Character {
private:
    int posX;
    int posY;
    int velX;
    int velY;
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
