#include "PeerManager.h"

PeerManager::PeerManager(Logger& logger) :
    mtx(),
    logger(logger)
{}

void PeerManager::push(Peer* peer){
    std::lock_guard<std::mutex> m(mtx);
    peers.push_back(peer);
}

void PeerManager::erase(int i){
    std::lock_guard<std::mutex> m(mtx);
    std::vector<Peer*>::iterator it = peers.begin() + i;
    (*it)->finish();
    delete *it;
    peers.erase(it);
    logger.infoMsg("Deleted player: " + std::to_string(i+1), __FILE__, __LINE__);
}

void PeerManager::start(int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->start();
}

void PeerManager::finish(int i) {
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->finish();
}

void PeerManager::send(Entity& entity, int i) {
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->send(entity);
}

void PeerManager::sendPointsLives(int i, int lives, int points) {
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->sendPointsLives(lives, points);
}

void PeerManager::sendBreak(int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->sendBreak();
}

std::string PeerManager::getName(int i){
    std::lock_guard<std::mutex> m(mtx);
    return peers[i]->getName();
}

void PeerManager::setName(std::string str, int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->setName(str);
}

void PeerManager::sendEndGame(int i, int end) {
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->sendEnd(end);
}

char PeerManager::receive(int i){
    std::lock_guard<std::mutex> m(mtx);
    return peers[i]->receive();
}

bool PeerManager::hasIncoming(int i) {
    return peers[i]->hasIncoming();
}

void PeerManager::receive(char* msg, int length, int i){
    peers[i]->receive(msg,length);
}

void PeerManager::send(char* msg, int length, int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->send(msg,length);
}

bool PeerManager::isDisconnected(int i){
    std::lock_guard<std::mutex> m(mtx);
    return peers[i]->isDisconnected();
}

bool PeerManager::isDisconnected(std::string name){
    std::lock_guard<std::mutex> m(mtx);
    for(int i = 0; i < peers.size(); i++){
        if(peers[i]->getName() == name){
            return peers[i]->isDisconnected();
        }
    }
    return true;
}

int PeerManager::getSize(){
    std::lock_guard<std::mutex> m(mtx);
    return peers.size();
}

void PeerManager::disconnectAll(){
    std::vector<Peer*>::iterator it = peers.begin();
    while(it != peers.end()){
        (*it)->finish();
        delete *it;
        peers.erase(it);
        logger.infoMsg("Deleted player", __FILE__, __LINE__);
    }
}

bool PeerManager::isReconnected(int i) {
    std::lock_guard<std::mutex> m(mtx);
    return peers[i]->isReconnected();
}

PeerManager::~PeerManager(){
}
