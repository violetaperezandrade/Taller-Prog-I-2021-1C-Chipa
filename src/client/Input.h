#ifndef INPUT_H
#define INPUT_H
#include "../common/Socket.h"
#include "../common/Thread.h"
#include <SDL2/SDL.h>

class Input : public Thread {
private:
    Socket& socket;
    bool quit;
public:
    Input(Socket& socket);

    ~Input();

    void run() override;

    void stop();
};

#endif //INPUT_H
