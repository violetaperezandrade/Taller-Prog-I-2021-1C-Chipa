#ifndef PEER_H
#define PEER_H

#include "../common/ProtectedQueue.h"
#include "../common/Socket.h"
#include "../common/BlockingQueue.h"
#include "../common/Entity.h"
#include "Sender.h"
#include "Receiver.h"
#include "../common/Logger.h"
#include "entities/Character.h"

class Peer {
private:
    Socket peer;
    Logger& logger;
    ProtectedQueue incoming;
    BlockingQueue outgoing;
    Sender* sender;
    Receiver* receiver;
    std::string name;
    bool disconnected;
    bool reconnected;

public:
    Peer(Socket&& peerSkt, Logger& logger, bool reconnected);

    ~Peer();

    void send(Entity& entity);

    void sendBreak();

    bool isReconnected();

    void start();

    char receive();

    bool hasIncoming();

    void receive(char* msg, int length);

    void send(char* msg, int length);

    void finish();

    std::string getName();

    void setName(std::string str);

    bool isDisconnected();

    void sendPointsLives(int lives, int points);

    void sendEnd(int end);

};

#endif //PEER_H
