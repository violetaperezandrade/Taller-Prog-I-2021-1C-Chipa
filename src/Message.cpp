#include "Message.h"

Message::Message() : info(NULL), size(0), empty(true) {}

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
        info = malloc(sizeof(char)*ENTITY_LEN);
    } else {
        info = realloc(sizeof(char)* (ENTITY_LEN + size));
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