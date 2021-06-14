#ifndef DONKEYKONG_CLIENTINPUT_H
#define DONKEYKONG_CLIENTINPUT_H
#include "../common/Socket.h"
#include "../common/Thread.h"

class ClientInput : public Thread {
private:
    Socket socket;
public:
    ClientInput(Socket socket);

    ~ClientInput();

    void run() override;
};

#endif //DONKEYKONG_CLIENTINPUT_H
