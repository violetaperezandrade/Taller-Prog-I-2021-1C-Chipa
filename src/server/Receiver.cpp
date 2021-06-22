#include "Receiver.h"

Receiver::Receiver(ProtectedQueue& queue, Socket& peerSkt, Logger& logger) :
    incoming(queue),
    peer(peerSkt),
    logger(logger),
    keepRunning(true)
{}

Receiver::~Receiver(){}

void Receiver::stop(){
    logger.debugMsg("Receiver Stop" , __FILE__, __LINE__);
    keepRunning = false;
    peer.shutdown(logger);
}

void Receiver::run(){
    while(keepRunning) {
        char c[1] = "";
        if(peer.receive(c, 1, logger) <= 0){
            logger.errorMsg("End of receiving", __FILE__, __LINE__);
            stop();
            c[0] = 'd';
        }
        incoming.push(c[0]);
        logger.debugMsg("Incoming push", __FILE__, __LINE__);
    }
}
