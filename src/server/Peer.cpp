#include "Peer.h"
#include "../common/protocols/EntityProtocol.h"

Peer::Peer(Socket &&peerSkt) :
    peer(peerSkt),
    sender(),
    receiver(),
    incoming(),
    outgoing()
{}

Peer::~Peer(){}

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