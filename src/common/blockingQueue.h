#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

template<class T>
class BlockingQueue {
private:
    std::queue<T> queue;
    std::mutex m;
    std::condition_variable condition_variable;

public:
    BlockingQueue() : queue(), m(), condition_variable() {}

    ~BlockingQueue() {}

    void push(T t) {
        std::unique_lock<std::mutex> lock(m);
        queue.push(std::move(t));
        condition_variable.notify_all();
    }

    T pop() {
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
