#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../common/Thread.h"
#include <vector>
#include "Monitor.h"
#include "../common/Socket.h"

class Processor : public Thread {
private:
    Monitor& monitor;
    Socket& socket;
    bool keepRunning;
public:
    Processor(Monitor& monitor, Socket& socket);
    void readEntities();
    void run() override;
    void stop();
    ~Processor();
};

#endif //PROCESSOR_H
