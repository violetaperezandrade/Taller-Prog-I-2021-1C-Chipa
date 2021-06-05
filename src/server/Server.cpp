#include "Server.h"
#include <chrono>
#include <thread>

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

    acceptClients();
    sktListener.shutdown();
    startGame();
}

void Server::startGame(){
    //todo send initial entities (all)
    std::chrono::milliseconds frameTime(30);
    bool finish = false;

    while(!finish) {
        std::chrono::steady_clock::time_point initialTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point timeSpan = initialTime + frameTime;
        for (int i = 0; i < playersAmount; i++) {
            while (clients[i].hasIncoming()) {
                clients[i].receive();
                //todo proccess receive
                //todo acá se puede hacer una factory o algo por el estilo
                //todo pero primero hay que traducirlo de protocolo
                //todo una vez que se que significa, sabiendo el numero de cliente
                //todo y el tipo de instrucción tengo que llamar a una cierta funcion de game
            }
        }

        game.update();
        finish = game.isFinished();
        //todo proccess send
        //todo for e in (entities on game): // all updated entities on game
        //      for c in clients:
        //          peer.send() Esto ya encola con protocolo y t0do y se hace el send
        std::this_thread::sleep_until(timeSpan);
    }
}

void Server::acceptClients(){
    int ready = 0;
    while(ready != playersAmount){
        Socket clientSkt = std::move(sktListener.accept());
        if(validateClient(clientSkt)){
            Peer client(std::move(clientSkt));
            clients.push_back(client);
            ready++;
        }
    }
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

Server::~Server() {}
