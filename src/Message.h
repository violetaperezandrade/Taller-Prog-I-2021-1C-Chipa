#ifndef MESSAGE_H
#define MESSAGE_H

#include "model/Entity.h"

class Message {
private:
    int size;
    char* info;
    bool empty;
    int pos;
public:
    Message();
    ~Message();
    Message(Message& message) = delete;
    Message(Message&& message);
    void add(Entity& entity);
    void getEntityInfo(char& type, int& posX, int& posY,
                       int& width, int& height, char& state);
    bool isEmpty();
    int getSize();
    char* getInfo();
};

#endif //MESSAGE_H
