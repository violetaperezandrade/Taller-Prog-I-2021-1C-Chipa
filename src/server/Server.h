#ifndef SERVER_H
#define SERVER_H

#include "Game.h"
#include "../common/Socket.h"
#include <vector>
#include <map>
#include <string>

class Server {
private:
    char* ip;
    char* port;
    int playersAmount;
    Game game;
    Socket sktListener;
    std::vector<Peer> clients;
    std::map<std::string, std::string> usersKeys;
    Config& config;
    Logger& logger;

public:
    Server(char* port, int playersAmount, Config& config, Logger& logger);

    void run();

    bool validateClient(Socket& skt);

    void acceptClients();

    void startGame();

    ~Server();
};


#endif //SERVER_H
