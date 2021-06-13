#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../common/Thread.h"
#include <vector>
#include "Monitor.h"

class Processor : public Thread {
private:
    Socket socket;

public:
    void readEntities();
    void run() override;
    void joinThread();
    Processor(std::vector<Entity>& vect, Socket skt);
    ~Processor();
};


#endif //PROCESSOR_H
