#include "Sender.h"

Sender::Sender(BlockingQueue& queue, Socket& peerSkt, Logger& logger) :
    outgoing(queue),
    peer(peerSkt),
    logger(logger)
{}

Sender::~Sender(){}

void Sender::stop(){
    peer.shutdownWrite();
}

void Sender::run() {
    std::pair<char*,int> msg = outgoing.pop();
    peer.send(std::get<0>(msg), std::get<1>(msg));
}