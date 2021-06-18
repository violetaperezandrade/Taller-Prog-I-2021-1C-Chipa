#include "Processor.h"
#include "../common/protocols/EntityProtocol.h"

Processor::Processor(Monitor& monitor, Socket& socket, Logger& logger) : monitor(monitor), socket(socket), logger(logger), keepRunning(true){}

void Processor::readEntities() {
    while(keepRunning) {
        if(EntityProtocol::readEntities(socket, monitor, logger) == 1){//llena el monitor con mensaje en bloque
            stop();
            return;
        }
        monitor.notify();
    }
}

void Processor::run() {
    readEntities();
}

void Processor::stop(){
    keepRunning = false;
    socket.shutdownRead(this->logger);
}

Processor::~Processor(){}