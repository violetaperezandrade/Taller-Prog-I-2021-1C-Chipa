#include "Peer.h"

Peer::Peer(Socket &&peerSkt) :
    peer(peerSkt),
    sender(),
    receiver(),
    incoming(),
    outgoing()
{}

Peer::~Peer(){}

void Peer::send(Entity& entity, char permanency) {

}

void sendBreak();

void receive();