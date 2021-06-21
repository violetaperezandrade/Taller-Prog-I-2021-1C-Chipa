#include "Processor.h"
#include "../common/protocols/EntityProtocol.h"
#include <chrono>

Processor::Processor(Monitor& monitor, Socket& socket, Logger& logger, bool& keepRunning) :
    monitor(monitor),
    socket(socket),
    logger(logger),
    keepRunning(keepRunning)
{}

void Processor::readEntities() {
    while(keepRunning) {
        if(EntityProtocol::readEntities(socket, monitor, logger) == 1){//llena el monitor con mensaje en bloque
            stop();
            return;
        }
        monitor.notify();
        std::chrono::milliseconds frameTime(1);
        std::chrono::steady_clock::time_point initialTime = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point timeSpan = initialTime + frameTime;
        std::this_thread::sleep_until(timeSpan);
        monitor.disnotify();
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