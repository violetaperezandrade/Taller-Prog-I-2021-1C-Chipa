#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../common/Thread.h"
#include <vector>
#include "Monitor.h"

class Processor : public Thread {
private:
    Monitor& monitor;
public:
    void readEntities();
    void run() override;
    void joinThread();
    Processor(Monitor& monitor);
    ~Processor();
};


#endif //PROCESSOR_H
