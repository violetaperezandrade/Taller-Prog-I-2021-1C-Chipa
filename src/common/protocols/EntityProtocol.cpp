#include "EntityProtocol.h"

#include "../Entity.h"

#define MSG_LEN 11

void EntityProtocol::writeChar(char* ptr, char num){
    ptr[0] = num;
}

void EntityProtocol::writeInt(char* ptr, int num){
    ptr[0] = (num >> 8) & 0xFF; // second to last byte
    ptr[1] = num & 0xFF; // last byte
}

void EntityProtocol::sendEntity(BlockingQueue& queue,
                                Entity entity) {
    char ptr[MSG_LEN];
    writeChar(ptr, entity.getType());
    writeInt(ptr+1, entity.getPosX());
    writeInt(ptr+3, entity.getPosY());
    writeInt(ptr+5, entity.getWidth());
    writeInt(ptr+7, entity.getHeight());
    writeChar(ptr+9, entity.getState());
    writeChar(ptr+10, entity.getPermanency());

    std::pair<char*, int> pair(ptr, MSG_LEN);
    queue.push(pair);
}

void EntityProtocol::sendBreak(BlockingQueue& queue) {
    char ptr[MSG_LEN];
    for(int i = 0; i < MSG_LEN; i++){
        ptr[i] = -1;
    }

    std::pair<char*, int> pair(ptr, MSG_LEN);
    queue.push(pair);
}

int EntityProtocol::getInt(char* ptr){
    int num = ptr[0] << 8;
    num += ptr[1];
    return num;
}

void EntityProtocol::readEntities(Socket &socket, Monitor& container, Logger& logger) {
    char buff[MSG_LEN];
    bool keepGoing = true;
    bool firstIteration = true;
    logger.debugMsg("Processor reading entities", __FILE__, __LINE__);

    container.cleanTemporary();
    while (keepGoing){
        socket.receive(buff, MSG_LEN, logger);
        if(buff[MSG_LEN - 1] == -1){
            keepGoing = false;
        } else if(firstIteration && buff[MSG_LEN - 1] == 1) {
            container.cleanPermanent();
            logger.debugMsg("Processor read permanent entity", __FILE__, __LINE__);
        }
        Entity entity(buff[0], getInt(buff+1), getInt(buff+3), getInt(buff+5),
                      getInt(buff+7), 0, 0, buff[9]);
        container.addEntity(entity);
        firstIteration = false;
    }
    logger.debugMsg("Processor read break", __FILE__, __LINE__);
}