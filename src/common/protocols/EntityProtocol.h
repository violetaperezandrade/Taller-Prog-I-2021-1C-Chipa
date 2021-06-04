#ifndef ENTITYPROTOCOL_H
#define ENTITYPROTOCOL_H

#include <vector>
#include "../Socket.h"

class EntityProtocol {
private:
    void writeChar(char* ptr, char num);
    void writeInt(char* ptr, int num);
    int getInt(char* ptr);
public:
    void sendEntity(Socket& socket, Entity entity,
                    char permanency);
    void sendBreak(Socket& socket);
    void readEntities(Socket& socket, EntityContainer& container);
};

#endif //ENTITYPROTOCOL_H
