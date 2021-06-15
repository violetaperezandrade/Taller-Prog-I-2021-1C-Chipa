#ifndef CLIENTINPUT_H
#define CLIENTINPUT_H
#include "../common/Socket.h"
#include "../common/Thread.h"

class ClientInput : public Thread {
private:
    Socket socket;
    bool quit;
public:
    ClientInput(Socket socket);

    ~ClientInput();

    void run() override;

    void stop();
};

#endif //CLIENTINPUT_H
