#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Config.h"
#include <map>
#include "Peer.h"
#include "PeerManager.h"

class LoginManager : public Thread {
private:
    PeerManager& peerManager;
    std::map<std::string,std::string> usersKeys;
    Config& config;
    Logger& logger;
    int clientNumber;
    std::map<std::string,int>& userNames;
public:
    LoginManager(PeerManager& peerManager, Config& config, Logger& logger, std::map<std::string,int>& userNames);

    ~LoginManager();

    void run() override;

    void validateLogin();
};


#endif //LOGINMANAGER_H
