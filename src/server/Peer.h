#ifndef PEER_H
#define PEER_H

#include <queue>
#include "../common/Socket.h"
#include "../common/BlockingQueue.h"
#include "Entity.h"

class Peer {
private:
    Socket peer;
    Sender sender;
    Receiver receiver;
    std::queue<char*> incoming;
    BlockingQueue<Entity> outgoing;
public:
    Peer(Socket&& peerSkt);

    ~Peer();
    void send();

    void sendBreak();

    void receive();
};

#endif //PEER_H
