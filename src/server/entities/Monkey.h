#ifndef MONKEY_H
#define MONKEY_H

#include "../../common/Entity.h"

class Monkey : public Entity {
public:
    Monkey(int posX, int posY, int width, int height, int speedX, int speedY);

    ~Monkey();
};
#endif //MONKEY_H
