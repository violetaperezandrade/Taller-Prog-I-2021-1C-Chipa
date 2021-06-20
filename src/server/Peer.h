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
    Logger& logger;
    std::queue<char> incoming;
    BlockingQueue outgoing;
    Sender* sender;
    Receiver* receiver;
    std::string name;

public:
    Peer(Socket&& peerSkt, Logger& logger);

    ~Peer();

    void send(Entity& entity);

    void sendBreak();

    void start();

    char receive();

    bool hasIncoming();

    void receive(char* msg, int length);

    void send(char* msg, int length);

    void finish();

    std::string getName();

    void setName(std::string str);

};

#endif //PEER_H
