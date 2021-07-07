#ifndef RECONNECTOR_H
#define RECONNECTOR_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Config.h"
#include <map>
#include "Peer.h"
#include <utility>
#include "PeerManager.h"

class Reconnector : public Thread {
private:
    PeerManager& peerManager;
    std::map<std::string,std::string> usersKeys;
    Config& config;
    Logger& logger;
    std::map<std::string,int>& userNames;
    int& keepRunning;
    Socket& sktListener;
public:
    Reconnector(PeerManager& peerManager, Config& config, Logger& logger,
                Socket& sktListener, std::map<std::string,int>& userNames, int& keepRunning);

    ~Reconnector();

    void run() override;

    void stop();

    void validateReconnection(Peer* client);
};


#endif //RECONNECTOR_H