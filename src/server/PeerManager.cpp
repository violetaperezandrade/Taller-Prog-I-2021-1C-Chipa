#include "PeerManager.h"

PeerManager::PeerManager(Logger& logger) :
    mtx(),
    logger()
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

char PeerManager::receive(int i){
    std::lock_guard<std::mutex> m(mtx);
    return peers[i]->receive();
}

bool PeerManager::hasIncoming(int i) {
    std::lock_guard<std::mutex> m(mtx);
    return peers[i]->hasIncoming();
}

void PeerManager::receive(char* msg, int length, int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->receive(msg,length, logger);
}

void PeerManager::send(char* msg, int length, int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->send(msg,length, logger);
}

bool PeerManager::isDisconnected(int i){
    std::lock_guard<std::mutex> m(mtx);
    peers[i]->isDisconnected();
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

PeerManager::~PeerManager(){
}
