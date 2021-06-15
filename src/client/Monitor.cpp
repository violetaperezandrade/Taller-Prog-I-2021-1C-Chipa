#include "Monitor.h"

Monitor::Monitor() : entities(), mtx(), cond_var() {}

Monitor::~Monitor() {}

void Monitor::addEntity(Entity& e){
    std::unique_lock<std::mutex> lock(mtx);
    entities.push_back(e);
}

std::vector<Entity> Monitor::getEntities(){
    std::unique_lock<std::mutex> lock(mtx);
    while(!notified){
        cond_var.wait(lock);
    }
    notified = false;
    return entities;
}

void Monitor::cleanPermanent(){
    const std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < entities.size(); i++){
        if (entities[i].getPermanency() == 1){ //es permanente
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

void Monitor::cleanTemporary(){
    const std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < entities.size(); i++){
        if (entities[i].getPermanency() == 0){ //es temporal
            entities.erase(entities.begin() + i);
            i--;
        }
    }
}

void Monitor::notify(){
    notified = true;
    cond_var.notify_all();
}