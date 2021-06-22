#ifndef RECONNECTOR_H
#define RECONNECTOR_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Config.h"
#include <map>
#include "Peer.h"
#include <utility>

class Reconnector : public Thread {
private:
    std::vector<Peer*>& peers;
    std::map<std::string,std::string> usersKeys;
    Config& config;
    Logger& logger;
    std::vector<std::string>& userNames;
    bool& keepRunning;
    Socket& sktListener;
public:
    Reconnector(std::vector<Peer*>& peers, Config& config, Logger& logger,
                Socket& sktListener, std::vector<std::string>& userNames, bool& keepRunning);

    ~Reconnector();

    void run() override;

    void stop();

    void validateReconnection(Peer* client);
};


#endif //RECONNECTOR_H