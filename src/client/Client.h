#ifndef CLIENT_H
#define CLIENT_H
#include "View.h"
#include "../common/Socket.h"
#include <vector>
#include "../server/Entity.h"

class Client {
private:
    Socket skt;
    View view;
    std::vector<Entity> staticEntities;
    std::vector<Entity> mobileEntities;
    char* ip;
    char* port;

public:
    Client(char* ip, char* port);
    void run();
    ~Client();
};


#endif //CLIENT_H
