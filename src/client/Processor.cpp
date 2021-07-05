#include "Processor.h"
#include "../common/protocols/EntityProtocol.h"
#include <chrono>

Processor::Processor(Monitor& monitor, Socket& socket, Logger& logger, bool& keepRunning, bool& serverActive, int& playerNumber) :
    monitor(monitor),
    socket(socket),
    logger(logger),
    keepRunning(keepRunning),
    serverActive(serverActive),
    playerNumber(playerNumber)
{}

void Processor::readEntities() {
    while(keepRunning && serverActive) {
        if(EntityProtocol::readInfo(socket, monitor, logger, playerNumber) == 1){//llena el monitor con mensaje en bloque
            serverActive = false;
            logger.debugMsg("Inactive server", __FILE__, __LINE__);
            monitor.notify();
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
    logger.debugMsg("Stop processor", __FILE__, __LINE__);
    keepRunning = false;
    socket.shutdown(this->logger);
}

Processor::~Processor(){}