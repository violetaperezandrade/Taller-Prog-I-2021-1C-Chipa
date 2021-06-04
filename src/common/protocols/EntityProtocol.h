#ifndef ENTITYPROTOCOL_H
#define ENTITYPROTOCOL_H

#include <vector>
#include "../Socket.h"

class EntityProtocol {
private:
    void receive(Socket& socket, char** input);
    int getLen(char* input);
public:
    void sendEntity(Socket& socket, Entity entity,
                    char permanency);
    void sendBreak(Socket& socket);
    void readEntities(Socket& socket, EntityContainer& container);
};

#endif //ENTITYPROTOCOL_H
