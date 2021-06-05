#ifndef SENDER_H
#define SENDER_H

#include "../common/Thread.h"

class Sender : public Thread {
private:
    BlockingQueue<Entity>& outgoing;
    Socket& peer;

public:
    Thread();

    ~Thread();

    void run() override;

};

#endif //SENDER_H
