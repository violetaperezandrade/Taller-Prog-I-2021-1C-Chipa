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
    Logger& logger;
public:
    LoginManager(Peer* client, Config& config, Logger& logger);

    ~LoginManager();

    void run() override;

    void validateLogin();
};


#endif //LOGINMANAGER_H
