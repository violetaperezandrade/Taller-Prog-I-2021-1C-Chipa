#include "LoginManager.h"

LoginManager::LoginManager(Peer& client, Config& config, Socket& skt) :
    client(client),
    config(config),
    skt(skt)
{
    usersKeys = config.getUserPass();
}

LoginManager::~LoginManager() {}

void LoginManager::run() {
    validate();
}

void LoginManager::validate(){
    char user[30];
    char password[30];
    char response[1]; //F for fail - G for good

    bool correctCredentials = false;
    while(!correctCredentials) {

        client.receive(user, 30);
        client.receive(password, 30);

        std::string usr(user);
        std::string pw(password);

        if (usersKeys[usr] != pw) {
            response[0] = 'F';
            skt.send(response, 1);
        }
    }
    response[0] = 'G';
    skt.send(response,1);
}