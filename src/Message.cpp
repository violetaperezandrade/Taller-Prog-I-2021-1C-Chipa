#include "Message.h"

#define ENTITY_LEN 10

Message::Message() : info(NULL), size(0), empty(true), pos(0) {}

Message::~Message() {
    if(info){
        free(info);
    }
}

void Message::write_char(char num){
    info[size++] = num;
}

void Message::write_int(int num){
    info[size++] = (num >> 8) & 0xFF; // second to last byte
    info[size++] = num & 0xFF; // last byte
}

void Message::add(Entity& entity) {
    if (empty){
        info = (char*) malloc(sizeof(char)*ENTITY_LEN);
        empty = false;
    } else {
        info = (char*) realloc(info, sizeof(char)* (ENTITY_LEN + size));
    }
    write_char(entity.getType());
    write_int(entity.getPosX());
    write_int(entity.getPosY());
    write_int(entity.getWidth());
    write_int(entity.getHeight());
    write_char(entity.getState());
}

int Message::get_size() {
    return size;
}

char* Message::get_info() {
    return info;
}

void Message::getEntityInfo(char& type, int& posX, int& posY,
                   int& width, int& height, char& state){
    if(this->isEmpty()){
        //throw error
        return;
    }
    type = info[pos++];
    posX = info[pos++] << 8;
    posX += info[pos++];
    posY = info[pos++] << 8;
    posY += info[pos++];
    width = info[pos++] << 8;
    width += info[pos++];
    height = info[pos++] << 8;
    height += info[pos++];
    state = info[pos++]; // podria poner que no haya un byte de
    // state cuando no corresponda
}
bool Message::isEmpty() {
    if (pos >= size){
        return true;
    }
    return false;
}

Message::Message(Message&& message) : info(message.info), size(message.size),
                                    empty(message.empty), pos(message.pos) {
    message.info = NULL;
}