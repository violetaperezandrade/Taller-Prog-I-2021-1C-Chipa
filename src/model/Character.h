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

    void run_left();

    void run_right();

    void move_left();

    void move_right();

    ~Character();

};


#endif
