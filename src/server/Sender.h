#ifndef SENDER_H
#define SENDER_H

#include "../common/Thread.h"
#include "../common/BlockingQueue.h"
#include "../common/Socket.h"

class Sender : public Thread {
private:
    BlockingQueue& outgoing;
    Socket& peer;
public:
    Sender(BlockingQueue& queue, Socket& peerSkt);

    ~Sender();

    void stop();

    void run() override;

};

#endif //SENDER_H
