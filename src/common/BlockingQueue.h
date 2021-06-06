#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>


class BlockingQueue {
private:
    std::queue<std::pair<char*,int>> queue;
    std::mutex m;
    std::condition_variable condition_variable;

public:
    BlockingQueue() : queue(), m(), condition_variable() {}

    ~BlockingQueue() {}

    void push(std::pair<char*,int> t) {
        std::unique_lock<std::mutex> lock(m);
        queue.push(std::move(t));
        condition_variable.notify_all();
    }

    std::pair<char*,int> pop() {
        std::unique_lock<std::mutex> lock(m);
        while(queue.empty()){
            condition_variable.wait(lock);
        }
        T t = std::move(queue.front());
        queue.pop();
        return t;
    }

    bool empty(){
        return queue.empty();
    }
};

#endif //BLOCKINGQUEUE_H
