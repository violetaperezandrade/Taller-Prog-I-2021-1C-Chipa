#include "Server.h"
#include <chrono>
#include <thread>
#include <string>
#include "../common/protocols/InputProtocol.h"
#include "LoginManager.h"
#include "Reconnector.h"

Server::Server(char* ip, char* port, int playersAmount, Config& config, Logger& logger) :
    ip(ip),
    port(port),
    playersAmount(playersAmount),
    game(config, logger, playersAmount),
    sktListener(),
    config(config),
    logger(logger),
    userNames(),
    keepRunning(true)
{}

void Server::run(){
    sktListener.bind(ip, port, logger);
    sktListener.listen(playersAmount, logger);

    acceptClients();
    Reconnector* reconnector = new Reconnector(clients, config, logger, sktListener,
                                               userNames, keepRunning);
    reconnector->start();
    startGame();
    reconnector->join();
    disconnectClients();
}

void Server::acceptClients(){
    std::vector<LoginManager*> logins;
    for(int i = 0; i != playersAmount; i++){
        Socket clientSkt = std::move(sktListener.accept(logger));
        Peer* client = new Peer(std::move(clientSkt), logger);
        clients.push_back(client);
        logger.infoMsg("Added peer number " + std::to_string(clients.size()), __FILE__, __LINE__);
        LoginManager* login = new LoginManager(client, config, logger);
        login->start();
        logins.push_back(login);
        logger.infoMsg("Login thread for peer launched", __FILE__, __LINE__);
    }

    std::vector<LoginManager*>::iterator it = logins.begin();
    while (it != logins.end()){
        (*it)->join();
        delete *it;
        it = logins.erase(it);
        logger.infoMsg("Login thread finished and erased", __FILE__, __LINE__);
    }

    for(int i = 0; i != playersAmount; i++){
        userNames.push_back(clients[i]->getName());
    }
}


void Server::disconnectClients(){
    for(int i = 0; i < playersAmount; i++){
        clients[i]->finish();
        delete clients[i];
        logger.infoMsg("Deleted player " + std::to_string(i+1), __FILE__, __LINE__);
    }
}

void Server::sendAll(){
    logger.debugMsg("Sending all entities to clients", __FILE__, __LINE__);
    std::vector<Entity>& entities = game.getEntities();
    std::vector<Character>& characters = game.getCharacters();

    for(int j = 0; j < entities.size(); j++){
        for(int i = 0; i < playersAmount; i++) {
            clients[i]->send(entities[j]);
        }
    }
    for(int j = 0; j < characters.size(); j++){
        for(int i = 0; i < playersAmount; i++) {
            clients[i]->send(characters[j]);
        }
    }
    for(int i = 0; i < playersAmount; i++){
        clients[i]->sendBreak();
    }
}

void Server::sendNew(){
    logger.debugMsg("Sending temporary entities to clients", __FILE__, __LINE__);
    std::vector<Entity>& entities = game.getEntities();
    std::vector<Character>& characters = game.getCharacters();

    for(int j = 0; j < entities.size(); j++){
        for(int i = 0; i < playersAmount; i++) {
            char c = entities[j].getPermanency();
            if(c == 'T'){
                clients[i]->send(entities[j]);
            }
        }
    }
    for(int j = 0; j < characters.size(); j++){
        for(int i = 0; i < playersAmount; i++) {
            clients[i]->send(characters[j]);
        }
    }
    for(int i = 0; i < playersAmount; i++){
        clients[i]->sendBreak();
    }
}

void Server::startClients(){
    logger.infoMsg("Starting the senders and receivers", __FILE__, __LINE__);
    for(int i = 0; i < playersAmount; i++){
        clients[i]->start();
    }
}

void Server::startGame(){
    logger.infoMsg("Game starts", __FILE__, __LINE__);
    startClients();
    sendAll();
    std::chrono::milliseconds frameTime(30);

    while(keepRunning) {
        logger.debugMsg("New game iteration", __FILE__, __LINE__);
        std::chrono::steady_clock::time_point initialTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point timeSpan = initialTime + frameTime;
        for (int i = 0; i < playersAmount; i++) {
            while (clients[i]->hasIncoming()) {
                char command = clients[i]->receive();
                makeCommand(command,i);
            }
        }
        game.update();
        sendNew();
        keepRunning = !game.isFinished();
        std::this_thread::sleep_until(timeSpan);
    }
    logger.infoMsg("Game finished", __FILE__, __LINE__);
}


void Server::makeCommand(char command,int i){
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
