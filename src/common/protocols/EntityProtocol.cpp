#include "EntityProtocol.h"

#include "../Entity.h"

#define ENTITY_MSG_LEN 11
#define STATS_MSG_LEN 11

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

void EntityProtocol::sendStats(BlockingQueue& queue, int lives, int points){
    EntityInfo info(lives, points);
    queue.push(info);
}

int EntityProtocol::getInt(char* ptr){
    int num = (unsigned char)ptr[0] << 8;
    num += (unsigned char)ptr[1];
    return num;
}

int EntityProtocol::getPoints(char* ptr){
    int num = (unsigned char) ptr[2];
    num = (num << 8) + (unsigned char) ptr[3];
    num = (num << 8) + (unsigned char) ptr[4];
    num = (num << 8) + (unsigned char) ptr[5];
    return num;
}

int EntityProtocol::readInfo(Socket &socket, Monitor& monitor, Logger& logger, int playerAmount, int& endGame){
    char buff[STATS_MSG_LEN];
    for (int i = 0; i < playerAmount; i++){
        int bytesRecv = socket.receive(buff, STATS_MSG_LEN, logger);
        if(bytesRecv <= 0){
            logger.errorMsg("Bytesrecv 0, socket closed", __FILE__, __LINE__);
            return 1;
        }
        if(buff[0] == 1){//Entonces EndGame
            endGame = buff[1];
            return 1;
        }
        char lives = buff[1];
        int points = getPoints(buff);
        monitor.addStats(lives, points);
    }
    return 0;
}

int EntityProtocol::readEntities(Socket &socket, Monitor& monitor, Logger& logger) {
    char buff[ENTITY_MSG_LEN];
    bool keepGoing = true;
    bool gotPermanent = false;
    logger.debugMsg("Processor reading entities", __FILE__, __LINE__);

    monitor.cleanTemporary();
    while (keepGoing){
        int bytesRecv = socket.receive(buff, ENTITY_MSG_LEN, logger);
        if(bytesRecv <= 0){
            logger.errorMsg("Bytesrecv 0, socket closed", __FILE__, __LINE__);
            return 1;
        }
        if(buff[ENTITY_MSG_LEN - 1] == -1){
            logger.debugMsg("Processor read break", __FILE__, __LINE__);
            keepGoing = false;
            continue;
        } else if(!gotPermanent && buff[ENTITY_MSG_LEN - 1] == 80) { //80 == P = Permanent
            monitor.cleanPermanent();                    // only when changing level or initial game
            gotPermanent = true;
        }
        Entity entity(buff[0], getInt(buff+1), getInt(buff+3), getInt(buff+5),
                      getInt(buff+7), 0, 0, buff[9], buff[10]);

        monitor.addEntity(entity);
    }

    logger.debugMsg("End of reading", __FILE__, __LINE__);
    return 0;
}

int EntityProtocol::read(Socket &socket, Monitor& monitor, Logger& logger, int playerAmount, int& endGame){
    if (readInfo(socket, monitor, logger, playerAmount, endGame) != 0){
        return 1;
    }
    return readEntities(socket, monitor, logger);
}

void EntityProtocol::sendEnding(BlockingQueue& queue, int end) {
    EntityInfo endInfo(end);
    queue.push(endInfo);
}