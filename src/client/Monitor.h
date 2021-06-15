#ifndef MONITOR_H
#define MONITOR_H
#include <condition_variable>
#include <mutex>
#include <iostream>
#include "../server/Entity.h"

class Monitor{
private:
    std::vector<Entity>& eVector;
    std::mutex m;
    std::condition_variable cond_var;
    bool notified = false;
public:
    Monitor() : eVector(), m(), cond_var() {}

    ~Monitor() {}

    void addEntity(Entity e){
        std::unique_lock<std::mutex> lock(m);
        eVector.push_back(e);
        notified = true;
        cond_var.notify_all();
    }

    Entity pop(){
        Entity e;
        std::unique_lock<std::mutex> lock(m);
        while(!notified){
            cond_var.wait(lock);
        }
        while (!eVector.empty()) {
            e = eVector.back();
        }
        notified = false;
        return e;
    }

    void cleanPermanent(){
        for (int i = 0; i < eVector.size(); i++){
            Entity e = eVector[i];
            if (e.getPermanency() == 1){ //es permanente
                const std::lock_guard<std::mutex> lock(m);
                eVector.erase(eVector.begin() + i);
            }
        }
    }

    void cleanTemporary(){
        for (int i = 0; i < eVector.size(); i++){
            Entity e = eVector[i];
            if (e.getPermanency() == 0){ //es temporal
                const std::lock_guard<std::mutex> lock(m);
                eVector.erase(eVector.begin() + i);
            }
        }
    }
    void empty(){
        eVector.clear();
    }
};
#endif //MONITOR_H
