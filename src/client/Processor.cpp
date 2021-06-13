#include "Processor.h"

Processor::Processor(std::vector<Entity>& vect,Socket skt) : socket(skt),entities(vect){}

void Processor::readEntities() {
    Monitor::setEntityVector(vect,socket);
}

void Processor::joinThread(){
    join();
}

void Processor::run() {
    readEntities();
}

Processor::~Processor(){};