#ifndef INPUT_H
#define INPUT_H
#include <SDL2/SDL.h>
#include "../common/Socket.h"
#include "../common/Thread.h"
#include "../common/Logger.h"

class Input : public Thread {
private:
    Socket& socket;
    bool quit;
    Logger& logger;
public:
    Input(Socket& socket, Logger& logger);

    ~Input() override;

    void run() override;

    void stop();
};

#endif //INPUT_H
