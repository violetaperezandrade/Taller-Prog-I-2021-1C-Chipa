#include "EntityProtocol.h"

#include "../Entity.h"

#define MSG_LEN 11

void EntityProtocol::sendEntity(BlockingQueue& queue,
                                Entity& entity) {
    EntityInfo info(entity.getType(), entity.getPosX(), entity.getPosY(),
               entity.getWidth(), entity.getHeight(), entity.getState(),
               entity.getPermanency());
    queue.push(info);
}

void EntityProtocol::sendBreak(BlockingQueue& queue) {
    EntityInfo info;
    queue.push(info);
}

int EntityProtocol::getInt(char* ptr){
    int num = (unsigned char)ptr[0] << 8;
    num += (unsigned char)ptr[1];
    return num;
}

int EntityProtocol::readEntities(Socket &socket, Monitor& container, Logger& logger) {
    char buff[MSG_LEN];
    bool keepGoing = true;
    bool gotPermanent = false;
    logger.debugMsg("Processor reading entities", __FILE__, __LINE__);

    container.cleanTemporary();
    while (keepGoing){
        int bytesRecv = socket.receive(buff, MSG_LEN, logger);
        if(bytesRecv == 0){
            logger.errorMsg("Bytesrecv 0, socket closed", __FILE__, __LINE__);
            return 1;
        }
        if(buff[MSG_LEN - 1] == -1){
            logger.debugMsg("Processor read break", __FILE__, __LINE__);
            keepGoing = false;
            continue;
        } else if(!gotPermanent && buff[MSG_LEN - 1] == 80) { //80 == P = Permanent
            container.cleanPermanent();                    // only when changing level or initial game
            gotPermanent = true;
        }
        Entity entity(buff[0], getInt(buff+1), getInt(buff+3), getInt(buff+5),
                      getInt(buff+7), 0, 0, buff[10]);

        container.addEntity(entity);
    }

    logger.debugMsg("End of reading", __FILE__, __LINE__);
    return 0;
}