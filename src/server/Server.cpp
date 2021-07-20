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
    peerManager(logger),
    config(config),
    logger(logger),
    userNames(),
    keepRunning(0)
{}

void Server::run(){
    sktListener.bind(ip, port, logger);
    sktListener.listen(playersAmount, logger);

    acceptClients();
    Reconnector* reconnector = new Reconnector(peerManager, config, logger, sktListener,
                                               userNames, keepRunning);
    reconnector->start();
    startGame();
    reconnector->stop();
    reconnector->join();
    sendEndGame();
    disconnectClients();
}

void Server::sendEndGame(){
    for(int i = 0; i < peerManager.getSize(); i++) {
        peerManager.sendEndGame(i, keepRunning);
    }
}

void Server::acceptClients(){
    std::vector<LoginManager*> logins;
    for(int i = 0; i != playersAmount; i++){
        Socket peerSkt = std::move(sktListener.accept(logger));
        Peer* client = new Peer(std::move(peerSkt), logger, false);
        peerManager.push(client);
        logger.infoMsg("Added peer number: " + std::to_string(peerManager.getSize() + 1), __FILE__, __LINE__);
        LoginManager* login = new LoginManager(peerManager, config, logger, userNames);
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
}


void Server::disconnectClients(){
    peerManager.disconnectAll();
}

void Server::sendAll(){
    logger.debugMsg("Sending all entities to clients", __FILE__, __LINE__);
    std::vector<Entity>& entities = game.getEntities();
    std::vector<Character>& characters = game.getCharacters();

    for(int j = 0; j < characters.size(); j++){
        for(int i = 0; i < peerManager.getSize(); i++) {
            peerManager.sendPointsLives(i, characters[j].getLives(), characters[j].getPoints());
        }
    }
    for(int j = 0; j < entities.size(); j++){
        for(int i = 0; i < peerManager.getSize(); i++) {
            peerManager.send(entities[j], i);
        }
    }
    for(int j = 0; j < characters.size(); j++){
        for(int i = 0; i < peerManager.getSize(); i++) {
            peerManager.send(characters[j], i);
        }
    }
    for(int i = 0; i < peerManager.getSize(); i++){
        peerManager.sendBreak(i);
    }
}

void Server::sendNew(){
    logger.debugMsg("Sending temporary entities to clients", __FILE__, __LINE__);
    std::vector<Entity>& entities = game.getEntities();
    std::vector<Character>& characters = game.getCharacters();

    for(int j = 0; j < characters.size(); j++){
        for(int i = 0; i < peerManager.getSize(); i++) {
            peerManager.sendPointsLives(i, characters[j].getLives(), characters[j].getPoints());
        }
    }
    for(int j = 0; j < entities.size(); j++){
        for(int i = 0; i < peerManager.getSize(); i++) {
            char c = entities[j].getPermanency();
            if(c == 'T'){
                peerManager.send(entities[j], i);
            }
        }
    }
    for(int j = 0; j < characters.size(); j++){
        for(int i = 0; i < peerManager.getSize(); i++) {
            peerManager.send(characters[j], i);
        }
    }
    for(int i = 0; i < peerManager.getSize(); i++){
        peerManager.sendBreak(i);
    }
}

void Server::startClients(){
    logger.infoMsg("Starting the senders and receivers", __FILE__, __LINE__);
    for(int i = 0; i < peerManager.getSize(); i++){
        peerManager.start(i);
    }
}

void Server::reconnect(int i, int currLevel){
    logger.infoMsg("Starting the senders and receivers for reconnected client", __FILE__, __LINE__);
    peerManager.start(i);

    logger.debugMsg("Sending all entities to reconnected client", __FILE__, __LINE__);
    std::vector<Entity>& entities = game.getEntities();
    std::vector<Character>& characters = game.getCharacters();

    for(int h = 0; h < currLevel; h++){
        for(int j = 0; j < peerManager.getSize(); j++) {
            peerManager.sendPointsLives(i, characters[j].getLives(), characters[j].getPoints());
        }
        for (int j = 0; j < entities.size(); j++) {
            peerManager.send(entities[j], i);
        }
        for (int j = 0; j < characters.size(); j++) {
            peerManager.send(characters[j], i);

        }
        peerManager.sendBreak(i);
    }
    game.reconnect(userNames[peerManager.getName(i)]);
}

void Server::startGame(){
    logger.infoMsg("Game starts", __FILE__, __LINE__);
    startClients();
    sendAll();
    std::chrono::milliseconds frameTime(30);
    int currLevel = 1;

    while(keepRunning == 0) {
        logger.debugMsg("New game iteration", __FILE__, __LINE__);
        std::chrono::steady_clock::time_point initialTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point timeSpan = initialTime + frameTime;
        for (int i = 0; i < peerManager.getSize(); i++) {
            if(peerManager.isReconnected(i)){
                reconnect(i, currLevel);
            }
            while (peerManager.hasIncoming(i)) {
                char command = peerManager.receive(i);
                makeCommand(command,userNames[peerManager.getName(i)]);
            }
            if(peerManager.isDisconnected(i)){
                game.disconnect(userNames[peerManager.getName(i)]);
                logger.infoMsg("Client " + std::to_string(i+1) + " disconnected", __FILE__, __LINE__);
                peerManager.erase(i);
            }
        }        
        if (game.update() && currLevel == 1){
            currLevel++;
            sendAll();
        } else {
            sendNew();
        }
        keepRunning = game.isFinished();
        std::this_thread::sleep_until(timeSpan);
        if(peerManager.getSize() == 0) {
            logger.infoMsg("All players disconnected no more game", __FILE__, __LINE__);
            keepRunning = 3;
        }
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
        case 'i':
            logger.debugMsg("Jugador invensible", __FILE__, __LINE__);
            game.setInvincible(i);
            break;
        default:
            logger.errorMsg("Llego un input invalido", __FILE__, __LINE__);
            break;
    }
}

Server::~Server() {}
