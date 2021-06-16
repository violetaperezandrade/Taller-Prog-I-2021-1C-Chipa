#ifndef ENTITYPROTOCOL_H
#define ENTITYPROTOCOL_H

#include <vector>
#include "../Socket.h"
#include "../BlockingQueue.h"
#include "../../client/Monitor.h"

class EntityProtocol {
private:
    static void writeChar(char* ptr, char num);
    static void writeInt(char* ptr, int num);
    static int getInt(char* ptr);
public:
    static void sendEntity(BlockingQueue& queue, Entity entity);
    static void sendBreak(BlockingQueue& queue);
    static void readEntities(Socket& socket, Monitor& container, Logger& logger);
};

#endif //ENTITYPROTOCOL_H
