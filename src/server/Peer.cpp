#include "Peer.h"
#include "../common/protocols/EntityProtocol.h"

Peer::Peer(Socket &&peerSkt) :
    peer(peerSkt),
    sender(new Sender),
    receiver(new Receiver),
    incoming(),
    outgoing()
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
    EntityProtocol::sendEntity(outcoming, entity);
}

void Peer::sendBreak(){
    EntityProtocol::sendBreak(outcoming);
}

char Peer::receive(){
    return incoming.pop();
}

bool Peer::hasIncoming() {
    return !incoming.empty();
}

void Peer::receive(char* msg, int length){
    peer.receive(msg,lenght);
}

void Peer::send(char* msh, int length){
    peer.send(msg,lenght);
}