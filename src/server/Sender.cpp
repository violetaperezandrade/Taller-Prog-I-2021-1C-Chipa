#include "Sender.h"

Sender::Sender(BlockingQueue<Entity>& queue, Socket& peerSkt) :
    outgoing(queue),
    peer(peerSkt)
{}

Sender::~Sender(){}

void Sender::stop(){
    socket.shutdownWrite();
}

void Sender::run() {
    std::pair<char*,int> msg = outgoing.pop();
    peer.send(std::get<0>msg, std::get<1>msg);
}