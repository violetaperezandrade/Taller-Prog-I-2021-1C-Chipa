/*#ifndef MONITOR_H
#define MONITOR_H
#include <mutex>
#include <vector>
#include <condition_variable>
#include <iostream>
#include <atomic>

class exMonitor {

private:
    std::vector<Entity>& entityVector;
    std::mutex vectorMutex;
    std::atomic<bool> state; //1 si el bloque fue leido, 0 si no
    std::condition_variable cond_var;
public:
    exMonitor(std::vector<Entity>&vect);
    void addEntity(Entity e);
    void cleanPermanent();
    void cleanTemporary();
    void cleanEntityVector();
    std::vector<Entity>& getEntityVector();
    bool getState();
    void setState(bool c);
    void notify();
    ~exMonitor();
};

#endif //MONITOR_H*/
