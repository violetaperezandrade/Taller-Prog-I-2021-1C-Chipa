#ifndef DONKEYKONG_CLIENTINPUT_H
#define DONKEYKONG_CLIENTINPUT_H
#include "../common/Socket.h"
#include "../common/Thread.h"

class ClientInput : public Thread {
private:
    Socket socket;
public:
    Sender(Socket socket);

    ~Sender();

    void run() override;
};

#endif //DONKEYKONG_CLIENTINPUT_H
