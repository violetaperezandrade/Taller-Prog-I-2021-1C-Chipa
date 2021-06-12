#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "../common/protocols/EntityProtocol.h"
#include "../common/Thread.h"
#include <mutex>


class Processor : public Thread {
private:
    std::mutex vectorMutex;
    Socket socket;
    //Recurso compartido
    std::vector<Entity>& entities;

public:
    void readEntities();
    void run() override;
    void joinThread();
    Processor(std::vector<Entity>& vect, Socket skt);
    ~Processor();
};


#endif //PROCESSOR_H
