#ifndef MONKEY_H
#define MONKEY_H

#include "../Entity.h"

class Monkey : public Entity {
public:
    Monkey(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Monkey();

    char getState() override;
};
#endif //MONKEY_H