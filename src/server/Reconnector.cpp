#include "Reconnector.h"

Reconnector::Reconnector(PeerManager& peerManager, Config& config, Logger& logger,Socket& sktListener,
                         std::map<std::string,int>& userNames, int& keepRunning) :
        peerManager(peerManager),
        config(config),
        logger(logger),
        userNames(userNames),
        keepRunning(keepRunning),
        sktListener(sktListener)
{
    usersKeys = config.getUserPass();
}

void Reconnector::run() {

    while (keepRunning == 0) {
        Socket peerSkt = std::move(sktListener.accept(logger));
        if(keepRunning == 0){
            Peer *client = new Peer(std::move(peerSkt), logger, true);
            logger.infoMsg("Added reconnected peer number " + std::to_string(peerManager.getSize()), __FILE__, __LINE__);
            validateReconnection(client);
            peerManager.push(client);
        }
    }
}

void Reconnector::validateReconnection(Peer* client){
    char user[30];
    char password[30];
    char response; //F for full - G for good - B for bad
    bool correctCredentials = false;
    bool alreadyPlayer = false;
    std::string finalUser;

    while(!correctCredentials && keepRunning == 0) {
        client->receive(user, 30);
        client->receive(password, 30);

        std::string usr(user);
        std::string pw(password);
        std::string empty;

        std::map<std::string,int>::iterator it = userNames.begin();
        while (it != userNames.end()) {
            if(it->first == usr){
                alreadyPlayer = true;
                logger.infoMsg("Reconnection correct credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
                client->setName(usr);
                break;
            }
            ++it;
        }
        if(alreadyPlayer) {
            if (usersKeys[usr] != pw || pw == empty || !peerManager.isDisconnected(usr)) {
                response = 'B';
                client->send(&response, 1);

                logger.infoMsg("Received incorrect credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
                continue;
            }
            correctCredentials = true;
            finalUser = usr;
            continue;
        }
        response = 'F';
        client->send(&response, 1);
        logger.infoMsg("Full game, no space for more players: " + usr + " " + pw, __FILE__, __LINE__);
        return;
    }
    if(keepRunning != 0) return;
    response = userNames[finalUser]+1;
    client->send(&response,1);
}

void Reconnector::stop(){
    sktListener.shutdown(logger);
    logger.debugMsg("Reconnector shutdown", __FILE__, __LINE__);
}

Reconnector::~Reconnector() {}

