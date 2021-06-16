#include "Receiver.h"

Receiver::Receiver(std::queue<char>& queue, Socket& peerSkt, Logger& logger) :
    incoming(queue),
    peer(peerSkt),
    logger(logger)
{}

Receiver::~Receiver(){}

void Receiver::stop(){
    peer.shutdownRead();
}

void Receiver::run(){
    char c[1] = "";
    peer.receive(c,1);
    incoming.push(c[0]);
}
