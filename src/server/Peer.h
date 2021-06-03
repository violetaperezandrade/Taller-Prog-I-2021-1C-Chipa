#ifndef PEER_H
#define PEER_H

#include "../common/Socket.h"

class Peer {
private:
    Socket peer;
    //Thread Sender
    //Thread Receiver
public:
    Peer(Socket&& peerSkt) : peer(peerSkt){}
    ~Peer();
    void send();
    void receive();
};

#endif //PEER_H
