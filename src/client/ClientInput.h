#ifndef DONKEYKONG_CLIENTINPUT_H
#define DONKEYKONG_CLIENTINPUT_H
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

#endif //DONKEYKONG_CLIENTINPUT_H
