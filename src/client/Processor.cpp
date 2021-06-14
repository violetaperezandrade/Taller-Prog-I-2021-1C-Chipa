#include "Processor.h"

Processor::Processor(Monitor& monitor) : monitor(monitor){}

void Processor::readEntities() {
    monitor.setEntityVector();
}

void Processor::run() {
    while (//no reciba eof){
        readEntities();
    }
    monitor.cleanEntityVector();
}

Processor::~Processor(){}