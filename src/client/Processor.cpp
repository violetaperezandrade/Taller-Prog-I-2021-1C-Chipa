#include "Processor.h"
#include "../common/protocols/EntityProtocol.h"

Processor::Processor(Monitor& monitor, Socket& socket) : monitor(monitor), socket(socket){}

void Processor::readEntities() {
    EntityProtocol::readEntities(socket, monitor);
}

void Processor::run() {
    readEntities();
    monitor.setState(false);
    monitor.notify();
}

void Processor::close(){
    socket.shutdownRead();

}

Processor::~Processor(){}