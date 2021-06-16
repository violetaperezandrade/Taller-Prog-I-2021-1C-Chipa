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
        peer.send(std::get<0>(msg), std::get<1>(msg), logger);
        logger.debugMsg("Sender send", __FILE__, __LINE__);
    }
}