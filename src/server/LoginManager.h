#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Config.h"
#include <map>
#include "Peer.h"

class LoginManager : public Thread {
private:
    Peer* client;
    std::map<std::string,std::string> usersKeys;
    Config& config;
    Socket& skt;
    Logger& logger;
public:
    LoginManager(Peer* client, Config& config, Socket& skt, Logger& logger);

    ~LoginManager();

    void run() override;

    void validate();
};


#endif //LOGINMANAGER_H
