#ifndef SENDER_H
#define SENDER_H

#include "../common/Thread.h"

class Sender : public Thread {
private:
    BlockingQueue<Entity>& outgoing;
    Socket& peer;
public:
    Sender(BlockingQueue<Entity>& queue, Socket& peerSkt);

    ~Sender();

    void stop();

    void run() override;

};

#endif //SENDER_H
