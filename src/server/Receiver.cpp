#include "Receiver.h"

Receiver::Receiver(std::queue<char>& queue, Socket& peerSkt) :
    incoming(queue),
    peer(peerSkt)
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
