#ifndef MESSAGE_H
#define MESSAGE_H

#include "model/Entity.h"

class Message {
private:
    int size;
    char* info;
    bool empty;
public:
    Message();
    ~Message();
    void add(Entity& entity);
    int get_size();
    char* get_info();
};

#endif //MESSAGE_H
