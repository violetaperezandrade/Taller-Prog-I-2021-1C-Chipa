#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

#include "Logger.h"

//podría ser un template
class BlockingQueue {
private:
    std::queue<std::pair<char*,int>> queue;
    std::mutex m;
    std::condition_variable condition_variable;
    Logger& logger;

public:
    BlockingQueue(Logger& logger) : queue(), m(), condition_variable(), logger(logger) {}

    ~BlockingQueue() {}

    void push(std::pair<char*,int> t) {
        std::unique_lock<std::mutex> lock(m);
        queue.push(std::move(t));
        condition_variable.notify_all();
        logger.debugMsg("Blocking queue push and notify all" , __FILE__, __LINE__);
    }

    std::pair<char*,int> pop() {
        std::unique_lock<std::mutex> lock(m);
        logger.debugMsg("Blocking queue pop" , __FILE__, __LINE__);
        while(queue.empty()){
            logger.debugMsg("Queue empty waiting for pushing" , __FILE__, __LINE__);
            condition_variable.wait(lock);
        }
        logger.debugMsg("Blocking queue pop" , __FILE__, __LINE__);
        std::pair<char*,int> t = std::move(queue.front());
        queue.pop();
        return t;
    }

    bool empty(){
        return queue.empty();
    }
};

#endif //BLOCKINGQUEUE_H
