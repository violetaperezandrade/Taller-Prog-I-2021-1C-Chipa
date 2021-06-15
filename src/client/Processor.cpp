#include "Processor.h"
#include "../common/protocols/EntityProtocol.h"

Processor::Processor(Monitor& monitor, Socket& socket) : monitor(monitor), socket(socket){}

void Processor::readEntities() {
    std::vector<Entity>& entities = monitor.getEntityVector();
    EntityProtocol::readEntities(socket, entities);
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