#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class StateManager {
private:
    char mode;
public:
    StateManager();
    ~StateManager();
    void setStandardMode();
    void setHammerMode();
    char getFallingRight();
    char getFallingLeft();
    char getMovingRight();
    char getMovingLeft();
    char getMovingUp();
    char getMovingDown();
    char getIdleRight();
    char getIdleLeft();
    char getIdleOff();
};

#endif //STATEMANAGER_H
