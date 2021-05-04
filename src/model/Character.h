#ifndef DONKEYKONG_CHARACTER_H
#define DONKEYKONG_CHARACTER_H

class Character {
private:
    int posX;
    int posY;
    int speedX;
    int speedY;
    int state;
public:
    Character();

    void jump();

    void runLeft();

    void runRight();

    void moveLeft(int& i);

    void moveRight(int& i);

    ~Character();

};


#endif
