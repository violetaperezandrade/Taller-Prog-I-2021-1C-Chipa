#ifndef MONITOR_H
#define MONITOR_H
#include "../common/protocols/EntityProtocol.h"
#include <mutex>
#include <vector>

class Monitor {

private:
    std::vector<Entity>& entityVector;
    std::mutex vectorMutex;
public:
    void setEntityVector(std::vector<Entity>& vect,Socket socket);
    std::vector<Entity>& getEntityVector();
};

#endif //MONITOR_H
