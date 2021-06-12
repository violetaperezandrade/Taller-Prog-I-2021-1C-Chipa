#ifndef LOGINMANAGER_H
#define LOGINMANAGER_H

#include "../common/Thread.h"
#include "../common/Socket.h"
#include "Peer.h"

class LoginManager : public Thread {
private:
    Peer& client;
public:
    LoginManager(Peer& client);

    ~LoginManager();

    void run() override;

    void validate();
};


#endif //LOGINMANAGER_H
