#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include "../common/Socket.h"
#include "../common/Thread.h"
#include "../common/Logger.h"
#include "View.h"


class Input : public Thread {
private:
    Socket& socket;
    bool& keepRunning;
    bool& serverActive;
    Logger& logger;
    bool& play;
public:
    Input(Socket& socket, Logger& logger, bool& keepRunning, bool& serverActive, bool& play);

    ~Input();

    void run() override;

    void stop();
};

#endif //INPUT_H