#include "Monitor.h"

void Monitor::setEntityVector(std::vector<Entity>& vect,Socket socket){
    const std::lock_guard<std::mutex> lock(vectorMutex);
    EntityProtocol::readEntities(&socket,vect);
}

std::vector<Entity>& Monitor::getEntityVector(){
    return entityVector;
}
