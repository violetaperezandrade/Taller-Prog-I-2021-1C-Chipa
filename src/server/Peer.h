#ifndef PEER_H
#define PEER_H

#include "../common/ProtectedQueue.h"
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
    ProtectedQueue<char> incoming;
    BlockingQueue outgoing;
    Sender* sender;
    Receiver* receiver;
    std::string name;
    bool disconnected;

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

    bool isDisconnected();

};

#endif //PEER_H
