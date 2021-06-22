#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <mutex>

class PeerManager {
private:
    std::vector<Peer*> peers;
    std::mutex mtx;
public:
    PeerManager();

    void push(Peer* peer);

    void erase(int i);

    ~PeerManager();
};


#endif //PEERMANAGER_H
