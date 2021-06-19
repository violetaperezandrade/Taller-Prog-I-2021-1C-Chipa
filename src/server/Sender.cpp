#include "Sender.h"

#include "../common/protocols/EntityInfo.h"

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
        EntityInfo info = outgoing.pop();
        if(peer.send((char*)info.getPtr(), info.getLen(), logger) <= 0){
            logger.errorMsg("Sending error", __FILE__, __LINE__);
            stop();
            break;
        }
        logger.debugMsg("Sender send", __FILE__, __LINE__);
    }
}