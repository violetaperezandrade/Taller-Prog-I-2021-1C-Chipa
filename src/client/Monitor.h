#ifndef MONITOR_H
#define MONITOR_H
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <vector>
#include "../common/Entity.h"
#include "../common/Logger.h"

#define MAX_PLAYERS 4

class Monitor{
private:
    char lives[MAX_PLAYERS];
    int points[MAX_PLAYERS];
    int pos;
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

    void getInfo(std::vector<Entity>& entities, int* points, int* lives);

    void cleanPermanent();

    void cleanTemporary();

    void disnotify();

    void notify();

    int getLevel();

    void addStats(int lives_aux, int points_aux);
};
#endif //MONITOR_H
