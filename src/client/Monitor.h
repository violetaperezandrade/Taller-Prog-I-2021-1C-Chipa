#ifndef MONITOR_H
#define MONITOR_H
#include <mutex>
#include <vector>
#include <condition_variable>

class Monitor {

private:
    std::vector<Entity>& entityVector;
    std::mutex vectorMutex;
    char state; //1 si el bloque fue leido, 0 si no
    std::condition_variable cond_var;
public:
    Monitor(std::vector<Entity>&vect);
    void addEntity(Entity e);
    void cleanPermanent();
    void cleanTemporary();
    void cleanEntityVector();
    std::vector<Entity>& getEntityVector();
    char getState();
    void setState(char c);
    void notify();
    ~Monitor();
}

#endif //MONITOR_H
