#include "Peer.h"
#include "../common/protocols/EntityProtocol.h"

Peer::Peer(Socket &&peerSkt) :
    peer(std::move(peerSkt)),
    incoming(),
    outgoing(),
    sender(new Sender(outgoing, peerSkt)),
    receiver(new Receiver(incoming, peer))
{
    sender->start();
    receiver->start();
}

void Peer::finish(){
    peer.shutdown();
    sender->join();
    receiver->join();
}

Peer::~Peer(){
    delete sender;
    delete receiver;
}

void Peer::send(Entity& entity) {
    EntityProtocol::sendEntity(outgoing, entity);
}

void Peer::sendBreak(){
    EntityProtocol::sendBreak(outgoing);
}

char Peer::receive(){
    char c = incoming.front();
    incoming.pop();
    return c;
}

bool Peer::hasIncoming() {
    return !incoming.empty();
}

void Peer::receive(char* msg, int length){
    peer.receive(msg,length);
}

void Peer::send(char* msg, int length){
    peer.send(msg,length);
}