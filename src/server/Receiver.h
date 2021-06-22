#ifndef RECEIVER_H
#define RECEIVER_H

#include "../common/ProtectedQueue.h"
#include "../common/Thread.h"
#include "../common/Socket.h"
#include "../common/Logger.h"

class Receiver : public Thread{
private:
    ProtectedQueue& incoming;
    Socket& peer;
    Logger& logger;
    bool keepRunning;
public:
    Receiver(ProtectedQueue& queue, Socket& peerSkt, Logger& logger);

    ~Receiver();

    void stop();

    void run() override;
};

#endif //RECEIVER_H
