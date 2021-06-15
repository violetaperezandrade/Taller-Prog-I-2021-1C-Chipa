#ifndef ENTITYPROTOCOL_H
#define ENTITYPROTOCOL_H

#include <vector>
#include "../Socket.h"
#include "../BlockingQueue.h"
#include "../../client/Monitor.h"

class EntityProtocol {
private:
    void writeChar(char* ptr, char num);
    void writeInt(char* ptr, int num);
    int getInt(char* ptr);
public:
    static void sendEntity(BlockingQueue& queue, Entity entity, char permanency);
    static void sendBreak(BlockingQueue& queue);
    static void readEntities(Socket& socket, Monitor& container);
};

#endif //ENTITYPROTOCOL_H
