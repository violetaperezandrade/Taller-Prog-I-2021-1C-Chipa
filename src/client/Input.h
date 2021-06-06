#ifndef DONKEYKONG_INPUT_H
#define DONKEYKONG_INPUT_H

#include "../common/Thread.h"

class Input : public Thread {
private:
    Socket socket;
    SDL_Window* window;
public:
    Sender(Socket socket);

    ~Sender();

    void run() override;

};


#endif //DONKEYKONG_SENDER_H
