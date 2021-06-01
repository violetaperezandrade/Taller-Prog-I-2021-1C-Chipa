#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread{
protected:
    std::thread thread;

public:
    Thread();

    void start();

    virtual void run() = 0;

    void join();

    virtual ~Thread();
};


#endif //THREAD_H
