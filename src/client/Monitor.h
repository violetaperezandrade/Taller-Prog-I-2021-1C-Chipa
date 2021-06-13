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
    Monitor(Socket& soket, std::vector<Entity>&vect);
    void setEntityVector();
    std::vector<Entity>& getEntityVector();
    ~Monitor();
};

#endif //MONITOR_H
