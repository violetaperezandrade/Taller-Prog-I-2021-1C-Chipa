#ifndef MONITOR_H
#define MONITOR_H
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <vector>
#include "../common/Entity.h"
#include "../common/Logger.h"

class Monitor{
private:
    std::vector<Entity> entities;
    std::mutex mtx;
    std::condition_variable cond_var;
    bool notified = false;
    Logger& logger;
    int level;
public:
    explicit Monitor(Logger& logger);

    ~Monitor();

    void addEntity(Entity& e);

    std::vector<Entity> getEntities();

    void cleanPermanent();

    void cleanTemporary();

    void disnotify();

    void notify();

    int getLevel();
};
#endif //MONITOR_H
