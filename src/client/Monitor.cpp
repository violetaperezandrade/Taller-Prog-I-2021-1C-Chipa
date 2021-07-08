#include "Monitor.h"

Monitor::Monitor(Logger& logger) :
    pos(0),
    entities(),
    mtx(),
    cond_var(),
    logger(logger),
    level(0)
    {}

Monitor::~Monitor() {}

void Monitor::addEntity(Entity& e){
    std::unique_lock<std::mutex> lock(mtx);
    entities.push_back(e);
    char c = e.getType();
    std::string s("Se agrega al container una entidad de tipo: ");
    s += c;
    logger.debugMsg(s, __FILE__, __LINE__);
}

void Monitor::getInfo(std::vector<Entity>& entities, int* points, int* lives){
    std::unique_lock<std::mutex> lock(mtx);
    while(!notified){
        cond_var.wait(lock);
    }
    logger.debugMsg("Get entities",__FILE__,__LINE__);
    entities = this->entities;
    for(int i = 0; i < 4; i++){
        points[i] = this->points[i];
        lives[i] = this->lives[i];
    }
    notified = false;
    return;
}

void Monitor::cleanPermanent(){
    const std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < entities.size(); i++){
        if (entities[i].getPermanency() == 'P'){ //es permanente
            entities.erase(entities.begin() + i);
            i--;
        }
    }
    level ++;
    logger.debugMsg("Se borran entidades permanentes",__FILE__,__LINE__);
}

void Monitor::cleanTemporary(){
    const std::lock_guard<std::mutex> lock(mtx);
    for (int i = 0; i < entities.size(); i++){
        if (entities[i].getPermanency() == 'T'){ //es temporal
            entities.erase(entities.begin() + i);
            i--;
        }
    }
    logger.debugMsg("Se borran entidades temporales",__FILE__,__LINE__);
}

void Monitor::disnotify(){
    notified = false;
}

void Monitor::notify(){
    notified = true;
    cond_var.notify_all();
    logger.debugMsg("Se notifica a las condition variables",__FILE__,__LINE__);
    pos = 0;
}

int Monitor::getLevel(){
    return this->level;
}

void Monitor::addStats(int lives_aux, int points_aux){
    const std::lock_guard<std::mutex> lock(mtx);
    lives[pos] = lives_aux;
    points[pos] = points_aux;
    pos++;
}