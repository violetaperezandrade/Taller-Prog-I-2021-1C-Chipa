#ifndef MONITOR_H
#define MONITOR_H
#include <mutex>
#include <vector>

class Monitor {

private:
    std::vector<Entity>& entityVector;
    std::mutex vectorMutex;
public:
    Monitor(std::vector<Entity>&vect);
    void addEntity(Entity e);
    void cleanPermanent();
    void cleanTemporary();
    void cleanEntityVector();
    std::vector<Entity>& getEntityVector();
    ~Monitor();
};

#endif //MONITOR_H
