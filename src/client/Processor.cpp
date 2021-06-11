#include "Processor.h"

Processor::Processor(std::vector<Entity>& vect,Socket skt) : socket(skt),entities(vect){}

void Processor::readEntities() {
    const std::lock_guard<std::mutex> lock(vectorMutex);
    EntityProtocol::readEntities(socket,entities);
}

void Processor::joinThread(){
    join();
}

void Processor::run() {
    readEntities();
}