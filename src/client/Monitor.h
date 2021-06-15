#ifndef MONITOR_H
#define MONITOR_H
#include <condition_variable>
#include <mutex>
#include <iostream>
#include "../server/Entity.h"

class Monitor{
private:
    std::vector<Entity> entities;
    std::mutex mtx;
    std::condition_variable cond_var;
    bool notified = false;

public:
    Monitor();

    ~Monitor();

    void addEntity(Entity& e);

    std::vector<Entity> getEntities();

    void cleanPermanent();

    void cleanTemporary();

    void notify();
};
#endif //MONITOR_H
