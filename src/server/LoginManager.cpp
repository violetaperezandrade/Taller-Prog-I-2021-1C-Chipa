#include "LoginManager.h"

LoginManager::LoginManager(PeerManager& peerManager, Config& config, Logger& logger) :
    peerManager(peerManager),
    config(config),
    logger(logger),
    clientNumber(peerManager.getSize())
{
    usersKeys = config.getUserPass();
}

LoginManager::~LoginManager() {}

void LoginManager::run() {
    validateLogin();
}

void LoginManager::validateLogin(){
    char user[30];
    char password[30];
    char response; //B for fail - G for good

    bool correctCredentials = false;
    while(!correctCredentials) {

        peerManager.receive(user, 30, clientNumber);
        peerManager.receive(password, 30, clientNumber);

        std::string usr(user);
        std::string pw(password);
        std::string empty;

        if (usersKeys[usr] != pw || pw == empty) {
            response = 'B';
            peerManager.send(&response, 1, clientNumber);

            logger.infoMsg("Received incorrect credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
            continue;
        }

        correctCredentials = true;
        logger.infoMsg("Received correct credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
        peerManager.setName(usr, clientNumber);
    }
    response = 'G';
    peerManager.send(&response,1, clientNumber);
}

