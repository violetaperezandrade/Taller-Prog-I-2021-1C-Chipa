#ifndef CLIENT_H
#define CLIENT_H
#include "View.h"
#include <vector>
#include "../server/Entity.h"
#include "../common/Logger.h"
#include "../server/Game.h"
#include "../server/Config.h"
#include "Login.h"
#include "ClientInput.h"
#include "Processor.h"

class Client {
private:
    Socket& skt;
    Logger& logger;
    std::vector<Entity> entities;
    char* ip;
    char* port;
    Config& config;

public:
    Client(char* ip, char* port, Logger& logger);
    void run();
    ~Client();
    int connect(char*ip, char* port);
    int send(const char* msg, size_t len);
    int recv(char* msg, size_t len);

    void run();
};


#endif //CLIENT_H
