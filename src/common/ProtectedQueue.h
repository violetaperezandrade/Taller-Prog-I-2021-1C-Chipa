#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <queue>
#include <mutex>

template<class T>
class ProtectedQueue {
private:
    std::queue<T> queue;
    std::mutex m;
public:
    ProtectedQueue() : queue(), m() {}
    ~ProtectedQueue() {}
    void push(T t){
        std::lock_guard<std::mutex> lock(m);
        queue.push(t);
    }
    T pop(){
        std::lock_guard<std::mutex> lock(m);
        T t;
        if (!queue.empty()){
            t = queue.front();
            queue.pop();
        }
        return t;
    }
    bool empty(){
        std::lock_guard<std::mutex> lock(m);
        return queue.empty();
    }
};

#endif //PROTECTEDQUEUE_H
