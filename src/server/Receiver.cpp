#include "Receiver.h"

Receiver::Receiver(std::queue<char>& queue, Socket& peerSkt, Logger& logger) :
    incoming(queue),
    peer(peerSkt),
    logger(logger),
    keepRunning(true)
{}

Receiver::~Receiver(){}

void Receiver::stop(){
    logger.debugMsg("Receiver Stop" , __FILE__, __LINE__);
    keepRunning = false;
    peer.shutdownRead(logger);
}

void Receiver::run(){
    while(keepRunning) {
        char c[1] = "";
        peer.receive(c, 1, logger);
        incoming.push(c[0]);
        logger.debugMsg("Incoming push", __FILE__, __LINE__);
    }
}
