#ifndef PEER_H
#define PEER_H

#include <queue>
#include "../common/Socket.h"
#include "../common/BlockingQueue.h"
#include "../common/Entity.h"
#include "Sender.h"
#include "Receiver.h"
#include "../common/Logger.h"

class Peer {
private:
    Socket peer;
    std::queue<char> incoming;
    BlockingQueue outgoing;
    Sender* sender;
    Receiver* receiver;
    Logger& logger;
public:
    Peer(Socket&& peerSkt, Logger& logger);

    ~Peer();

    void send(Entity& entity);

    void sendBreak();

    char receive();

    bool hasIncoming();

    void receive(char* msg, int length);

    void send(char* msg, int length);

    void finish();

};

#endif //PEER_H
