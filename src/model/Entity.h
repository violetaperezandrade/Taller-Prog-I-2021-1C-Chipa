#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
    int posX;
    int posY;
    int width;
    int height;
    int speedX;
    int speedY;

public:
    Entity(int x, int y, int width, int height);

    Entity(int posX, int posY, int width, int height, int speedX, int speedY);

    void setPosY(int& i);

    void setPosX(int& i);

    void setSpeedX(int& i);

    void setSpeedY(int& i);

    int getPosY();

    int getPosX();

    int getSpeedX();

    int getSpeedY();

    virtual ~Entity();
};

#endif //ENTITY_H
