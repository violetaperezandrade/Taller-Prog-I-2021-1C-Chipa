#include "Server.h"
#include <chrono>
#include <thread>
#include "../common/protocols/InputProtocol.h"

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
    disconnectClients();
}

void Server::disconnectClients(){
    for(int i = 0; i < playersAmount; i++){
        clients[i].finish();
    }
}

void Server::sendAll(){
    const std::vector<Entity>& entities = game.getEntities();
    const std::vector<Character>& characters = game.getPlayers();

    for(int i = 0; i < playersAmount; i++){
        for(int j = 0; j < entities.size(); j++){
            clients[i].send(entities[j]);
        }
        for(int j = 0; j < characters.size(); i++){
            clients[i].send(characters[j]);
        }
        clients[i].sendBreak();
    }
}

void Server::sendNew(){
    const std::vector<Entity>& entities = game.getEntities();
    const std::vector<Character>& players = game.getPlayers();

    for(int i = 0; i < playersAmount; i++){
        for(int j = 0; j < entities.size(); j++){
            char c = entities[j].getPermanency();
            if(c == '0'){
                clients[i].send(entities[j]);
            }
        }
        for(int j = 0; j < characters.size(); i++){
            clients[i].send(characters[i]);
        }
        clients[i].sendBreak();
    }
}

void Server::startGame(){
    sendAll();
    std::chrono::milliseconds frameTime(30);

    bool finish = false;
    while(!finish) {
        std::chrono::steady_clock::time_point initialTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point timeSpan = initialTime + frameTime;
        for (int i = 0; i < playersAmount; i++) {
            while (clients[i].hasIncoming()) {
                char command = clients[i].receive();
                makeCommand(c,i);
            }
        }
        game.update();
        sendNew();
        finish = game.isFinished();
        std::this_thread::sleep_until(timeSpan);
    }
}

void Server::acceptClients(){
    std::vector<LoginManager*> logins;
    for(int i = 0; i != playersAmount; i++){
        Socket clientSkt = std::move(sktListener.accept());
        Peer client(std::move(clientSkt));
        clients.push_back(client);
        LoginManager* login = new LoginManager(client);
        login->start();
        logins.push_back(login);
    }

    std::vector<LoginManager*>::iterator it = logins.begin();
    while (it != logins.end()){
        (*it)->join();
        delete *it;
        it = processors.erase(it);
    }
}

void Server::makeCommand(char& command,int& i){
    switch(command) {
        case PRESS_UP:
            logger.debugMsg("Se presiona boton UP", __FILE__, __LINE__);
            game.startMovingUp(i);
            break;
        case PRESS_DOWN:
            logger.debugMsg("Se presiona boton DOWN", __FILE__, __LINE__);
            game.startMovingDown(i);
            break;
        case PRESS_LEFT:
            logger.debugMsg("Se presiona boton LEFT", __FILE__, __LINE__);
            game.startMovingLeft(i);
            break;
        case PRESS_RIGHT:
            logger.debugMsg("Se presiona boton RIGHT", __FILE__, __LINE__);
            game.startMovingRight(i);
            break;
        case PRESS_JUMP:
            logger.debugMsg("Se presiona boton SPACE", __FILE__, __LINE__);
            game.startJumping(i);
            break;
        case RELEASE_UP:
            logger.debugMsg("Se libera boton UP", __FILE__, __LINE__);
            game.stopMovingUp(i);
            break;
        case RELEASE_DOWN:
            logger.debugMsg("Se libera boton DOWN", __FILE__, __LINE__);
            game.stopMovingDown(i);
            break;
        case RELEASE_LEFT:
            logger.debugMsg("Se libera boton LEFT", __FILE__, __LINE__);
            game.stopMovingLeft(i);
            break;
        case RELEASE_RIGHT:
            logger.debugMsg("Se libera boton RIGHT", __FILE__, __LINE__);
            game.stopMovingRight(i);
            break;
        case RELEASE_JUMP:
            logger.debugMsg("Se libera boton SPACE", __FILE__, __LINE__);
            game.stopJumping(i);
            break;
        default:
            break;
    }
}

Server::~Server() {}
