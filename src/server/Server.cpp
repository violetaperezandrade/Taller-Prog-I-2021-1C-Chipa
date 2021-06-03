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

    int ready = 0;
    while(ready != playersAmount){
        Socket clientSkt = std::move(sktListener.accept());
        if(validateClient(clientSkt)){
            Peer client(std::move(clientSkt));
            clients.push_back(client);
            ready++;
        }
    }
    sktListener.shutdown();

    startGame();
}

bool Server::validateClient(Socket& skt){
    char user[30];
    char password[30];
    char response[1]; //F for fail - G for good

    if(skt.receive(user,30) < 1) return false;
    if(skt.receive(password,30) < 1) return false;

    std::string usr(user);
    std::string pw(password);

    if(usersKeys[usr] != pw){
        response[0] = 'F';
        skt.send(buffer,1);
        return false;
    }
    responde[0] = 'G';
    skt.send(buffer,1);
    return true;
}

void Server::startGame(){

}
Server::~Server() {}
