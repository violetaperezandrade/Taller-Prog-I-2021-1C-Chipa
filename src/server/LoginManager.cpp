#include "LoginManager.h"

LoginManager::LoginManager(Peer* client, Config& config, Logger& logger) :
    client(client),
    config(config),
    logger(logger)
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

        client->receive(user, 30);
        client->receive(password, 30);

        std::string usr(user);
        std::string pw(password);
        std::string empty;

        if (usersKeys[usr] != pw || pw == empty) {
            response = 'B';
            client->send(&response, 1);

            logger.infoMsg("Received incorrect credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
            continue;
        }

        correctCredentials = true;
        logger.infoMsg("Received correct credentials. User: " + usr + " " + pw, __FILE__, __LINE__);
        client->setName(usr);
    }
    response = 'G';
    client->send(&response,1);
}

