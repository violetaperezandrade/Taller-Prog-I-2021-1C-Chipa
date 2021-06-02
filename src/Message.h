#ifndef MESSAGE_H
#define MESSAGE_H

#include "server/Entity.h"

class Message {
private:
    int size;
    unsigned char* info;
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
    int get_size();
    unsigned char* get_info();
    void write_char(char num);
    void write_int(int num);
};

#endif //MESSAGE_H
