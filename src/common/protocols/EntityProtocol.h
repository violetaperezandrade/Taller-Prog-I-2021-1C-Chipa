#ifndef ENTITYPROTOCOL_H
#define ENTITYPROTOCOL_H

#include <vector>
#include "../Socket.h"
#include "../BlockingQueue.h"
#include "../../client/Monitor.h"

class EntityProtocol {
private:
    static int getInt(char* ptr);
    static int getPoints(char* ptr);
    static int readStats(Socket& socket, Monitor& container, Logger& logger, int playerNumber);
    static int readEntities(Socket& socket, Monitor& container, Logger& logger);
public:
    static void sendEntity(BlockingQueue& queue, Entity& entity);
    static void sendBreak(BlockingQueue& queue);
    static void sendStats(BlockingQueue& queue, int lives, int points);
    static int readInfo(Socket &socket, Monitor& monitor, Logger& logger, int player_number);
    static void sendEnding(BlockingQueue& queue, int end);
};

#endif //ENTITYPROTOCOL_H
