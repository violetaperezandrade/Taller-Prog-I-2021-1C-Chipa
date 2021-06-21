#include "Reconnector.h"

Reconnector::Reconnector(std::vector<Peer*>& clients, Config& config, Logger& logger,Socket& sktListener,
                           std::vector<std::string>& userNames, bool& keepRunning) :
        clients(clients),
        config(config),
        logger(logger),
        userNames(userNames),
        keepRunning(keepRunning),
        sktListener(sktListener)
{
    usersKeys = config.getUserPass();
}

void Reconnector::run() {

    while (keepRunning) {
        Socket clientSkt = std::move(sktListener.accept(logger));
        if(keepRunning){
            Peer *client = new Peer(std::move(clientSkt), logger);
            logger.infoMsg("Added reconnected peer number " + std::to_string(clients.size()), __FILE__, __LINE__);
            validateReconnection(client);
            clients.push_back(client);
        }
    }
}

void Reconnector::validateReconnection(Peer* client){
    char user[30];
    char password[30];
    char response; //F for full - G for good - B for bad
    bool correctCredentials = false;
    bool alreadyPlayer = false;

    while(!correctCredentials && keepRunning) {

        client->receive(user, 30);
        client->receive(password, 30);

        std::string usr(user);
        std::string pw(password);
        std::string empty;

        std::vector<std::string>::iterator it = userNames.begin();
        while (it != userNames.end()) {
            if(*it == usr){
                alreadyPlayer = true;
                logger.infoMsg("Reconnection correct credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
                client->setName(usr);
                break;
            }
            ++it;
        }
        if(alreadyPlayer) {
            if (usersKeys[usr] != pw || pw == empty) {
                response = 'B';
                client->send(&response, 1);

                logger.infoMsg("Received incorrect credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
                continue;
            }
            correctCredentials = true;
            continue;
        }
        response = 'F';
        client->send(&response, 1);
        logger.infoMsg("Full game, no space for more players: " + usr + " " + pw, __FILE__, __LINE__);
        return;
    }
    if(!keepRunning) return;
    response = 'G';
    client->send(&response,1);
}

void Reconnector::stop(){
    sktListener.shutdown(logger);
    logger.debugMsg("Reconnector shutdown", __FILE__, __LINE__);
}

Reconnector::~Reconnector() {}

