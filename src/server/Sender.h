#ifndef SENDER_H
#define SENDER_H

#include "../common/Thread.h"
#include "../common/BlockingQueue.h"
#include "../common/Socket.h"
#include "../common/Logger.h"

class Sender : public Thread {
private:
    BlockingQueue& outgoing;
    Socket& peer;
    Logger& logger;
    bool keepRunning;

public:
    Sender(BlockingQueue& queue, Socket& peerSkt, Logger& logger);

    ~Sender();

    void stop();

    void run() override;

};

#endif //SENDER_H
