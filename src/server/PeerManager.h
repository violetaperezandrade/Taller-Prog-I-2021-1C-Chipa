#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <mutex>
#include "Peer.h"

class PeerManager {
private:
    std::mutex mtx;
    Logger& logger;
    std::vector<Peer*> peers;
public:
    PeerManager(Logger& logger);

    void push(Peer* peer);

    void erase(int i);

    void start(int i);

    void finish(int i);

    void send(Entity& entity, int i);

    void sendBreak(int i);

    std::string getName(int i);

    void setName(std::string str, int i);

    char receive(int i);

    bool hasIncoming(int i);

    void receive(char* msg, int length, int i);

    void send(char* msg, int length, int i);

    bool isDisconnected(int i);

    int getSize();

    void disconnectAll();

    bool isReconnected(int i);

    ~PeerManager();
};


#endif //PEERMANAGER_H
