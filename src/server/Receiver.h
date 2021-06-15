#ifndef RECEIVER_H
#define RECEIVER_H

#include <queue>
#include "../common/Thread.h"
#include "../common/Socket.h"


class Receiver : public Thread{
private:
    std::queue<char>& incoming;
    Socket& peer;
public:
    Receiver(std::queue<char>& queue, Socket& peerSkt);

    ~Receiver();

    void stop();

    void run() override;
};

#endif //RECEIVER_H
