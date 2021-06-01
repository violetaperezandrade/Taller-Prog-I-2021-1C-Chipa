#include "Server.h"

Server::Server(char* port, int playersAmount, Config& config, Logger& logger) :
    ip(c_str("127.0.0.1")),
    port(port),
    playersAmount(playersAmount),
    game(config, logger),
    sktListener(),
    config(config),
    logger(logger)
{}

void Server::run(){
    sktListener.bind(ip, port);
    sktListener.listen(playersAmount);

    for(int i = 0; i < playersAmount, i++){
        Peer client(sktListener.accept());
        clients.push_back(client);
        clients[i].validate();
    }
}


Server::~Server() {}
