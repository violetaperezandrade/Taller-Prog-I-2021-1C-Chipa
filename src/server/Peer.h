#ifndef PEER_H
#define PEER_H

#include <queue>
#include "../common/Socket.h"
#include "../common/BlockingQueue.h"

class Peer {
private:
    Socket peer;
    Sender sender;
    Receiver receiver;
    std::queue<char*> incoming;
    BlockingQueue<std::pair<char*,int>> outgoing;
public:
    Peer(Socket&& peerSkt) : peer(peerSkt){}
    ~Peer();
    void send();
    void receive();
};

#endif //PEER_H
