#include "Monitor.h"

Monitor::Monitor(std::vector<Entity>& vect) : entityVector(vect){}

void Monitor::addEntity(Entity e){
    const std::lock_guard<std::mutex> lock(vectorMutex);
    vect.push_back(e);
}

void Monitor::cleanPermanent(Entity e){
    for (int i = 0, i < vect.size(), i++){
        Entity e = vec(i);
        if (e.getPermanency == 1){ //es permanente
            const std::lock_guard<std::mutex> lock(vectorMutex);
            vect.erase(i);
        }
    }
}

void Monitor::cleanTemporary(Entity e){
    for (int i = 0, i < vect.size(), i++){
        Entity e = vec(i);
        if (e.getPermanency == 0){ //es temporal
            const std::lock_guard<std::mutex> lock(vectorMutex);
            vect.erase(i);
        }
    }
}

void Monitor::cleanEntityVector(){
    Monitor::cleanPermanent();
    Monitor::cleanTemporary();
}

std::vector<Entity>& Monitor::getEntityVector(){
    return entityVector;
}

Monitor::~Monitor() {}
