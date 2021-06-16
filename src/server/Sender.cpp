#include "Sender.h"

Sender::Sender(BlockingQueue& queue, Socket& peerSkt, Logger& logger) :
    outgoing(queue),
    peer(peerSkt),
    logger(logger),
    keepRunning(true)
{}

Sender::~Sender(){}

void Sender::stop(){
    peer.shutdownWrite(logger);
    keepRunning = false;
    logger.debugMsg("Sender stop" , __FILE__, __LINE__);
}

void Sender::run() {
    while(keepRunning) {
        std::pair<char *, int> msg = outgoing.pop();
        if(peer.send(std::get<0>(msg), std::get<1>(msg), logger) <= 0){
            logger.errorMsg("Sending error", __FILE__, __LINE__);
            stop();
            break;
        }
        logger.debugMsg("Sender send", __FILE__, __LINE__);
    }
}