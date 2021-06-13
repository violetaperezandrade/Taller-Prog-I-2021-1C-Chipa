#include "Processor.h"

Processor::Processor(Monitor& monitor) : monitor(monitor){}

void Processor::readEntities() {
    monitor.setEntityVector();
}

void Processor::joinThread(){
    join();
}

void Processor::run() {
    readEntities();
}

Processor::~Processor(){};