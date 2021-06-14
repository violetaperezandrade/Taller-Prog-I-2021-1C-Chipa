#ifndef MONITOR_H
#define MONITOR_H
#include "../common/protocols/EntityProtocol.h"
#include <mutex>
#include <vector>

class Monitor {

private:
    Socket& socket;
    std::vector<Entity>& entityVector;
    std::mutex vectorMutex;
public:
    Monitor(Socket& socket, std::vector<Entity>&vect);
    void setEntityVector();
    void cleanEntityVector();
    std::vector<Entity>& getEntityVector();
    void stop();
    ~Monitor();
};

#endif //MONITOR_H
