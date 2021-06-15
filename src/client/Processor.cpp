#include "Processor.h"
#include "../common/protocols/EntityProtocol.h"

Processor::Processor(Monitor& monitor, Socket& socket) : monitor(monitor), socket(socket), keepRunning(true){}

void Processor::readEntities() {
    while(keepRunning) {
        EntityProtocol::readEntities(socket, monitor);
        monitor.notify();
    }
}

void Processor::run() {
    readEntities();
}

void Processor::stop(){
    keepRunning = false;
    socket.shutdownRead();
}

Processor::~Processor(){}