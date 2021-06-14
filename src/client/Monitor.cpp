#include "Monitor.h"

Monitor::Monitor(Socket& socket,std::vector<Entity>& vect) : socket(socket),entityVector(vect){}

void Monitor::setEntityVector(){
    const std::lock_guard<std::mutex> lock(vectorMutex);
    EntityProtocol::readEntities(socket,vect);
}

std::vector<Entity>& Monitor::getEntityVector(){
    return entityVector;
}

Monitor::~Monitor{
    socket.shutdownRead();
};