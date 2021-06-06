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
    BlockingQueue<std::pair<char*,int>> outgoing;
public:
    Peer(Socket&& peerSkt);

    ~Peer();

    void send(Entity& entity);

    void sendBreak();

    char receive();

    bool hasIncoming();
};

#endif //PEER_H
