#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <queue>
#include <mutex>

//maybe a template
class ProtectedQueue {
private:
    std::queue<char> queue;
    std::mutex m;
public:
    ProtectedQueue() : queue(), m() {}
    ~ProtectedQueue() {}
    void push(char t){
        std::lock_guard<std::mutex> lock(m);
        queue.push(t);
    }
    char pop(){
        std::lock_guard<std::mutex> lock(m);
        char t;
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

    char front(){
        std::lock_guard<std::mutex> lock(m);
        if(queue.empty()) return 0;
        return queue.front();
    }
};

#endif //PROTECTEDQUEUE_H
