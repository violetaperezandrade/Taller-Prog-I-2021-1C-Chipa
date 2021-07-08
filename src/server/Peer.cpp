#include "Peer.h"
#include "../common/protocols/EntityProtocol.h"

Peer::Peer(Socket &&peerSkt, Logger& logger, bool reconnected) :
    peer(std::move(peerSkt)),
    logger(logger),
    incoming(),
    outgoing(logger),
    sender(new Sender(outgoing, peer, logger)),
    receiver(new Receiver(incoming, peer, logger)),
    name(),
    disconnected(false),
    reconnected(reconnected)
{
}

void Peer::start(){
    sender->start();
    receiver->start();
}

void Peer::finish(){
    receiver->join();
    logger.infoMsg("Receiver join", __FILE__, __LINE__);
    sender->stop();
    sendBreak();
    sender->join();
    logger.debugMsg("Sender join", __FILE__, __LINE__);
}

Peer::~Peer(){
    delete sender;
    delete receiver;
}

void Peer::send(Entity& entity) {
    EntityProtocol::sendEntity(outgoing, entity);
}

void Peer::sendBreak(){
    EntityProtocol::sendBreak(outgoing);
}

std::string Peer::getName(){
    return name;
}

void Peer::setName(std::string str){
    name = str;
}

char Peer::receive(){
    char c = incoming.pop();
    return c;
}

bool Peer::hasIncoming() {
    char front = incoming.front();
    if(front == 'd'){
        disconnected = true;
        incoming.pop();
        return false;
    }
    return front != '\0';
}

void Peer::receive(char* msg, int length){
    peer.receive(msg,length,logger);
}

void Peer::send(char* msg, int length){
    peer.send(msg,length,logger);
}

bool Peer::isDisconnected(){
    return disconnected;
}

bool Peer::isReconnected(){
    if(reconnected){
        reconnected = false;
        return true;
    }
    return false;
}

void Peer::sendPointsLives(int lives, int points) {
    EntityProtocol::sendStats(outgoing, lives, points);
}

void Peer::sendEnd(int end){
    EntityProtocol::sendEnding(outgoing, end);
}