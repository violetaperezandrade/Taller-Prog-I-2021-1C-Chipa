#ifndef SERVER_H
#define SERVER_H

#include "Game.h"
#include "../common/Socket.h"
#include "Peer.h"
#include <vector>
#include <map>
#include <string>
#include "PeerManager.h"

class Server {
private:
    char* ip;
    char* port;
    int playersAmount;
    Game game;
    Socket sktListener;
    PeerManager peerManager;
    std::map<std::string, std::string> usersKeys;
    Config& config;
    Logger& logger;
    std::map<std::string,int> userNames;
    int keepRunning;

public:
    Server(char* ip, char* port, int playersAmount, Config& config, Logger& logger);

    void run();

    void reconnect(int i, int actLevel);

    void acceptClients();

    void startGame();

    void sendNew();

    void startClients();

    void sendAll();

    void disconnectClients();

    void makeCommand(char command,int i);

    void sendEndGame();

    ~Server();
};


#endif //SERVER_H
