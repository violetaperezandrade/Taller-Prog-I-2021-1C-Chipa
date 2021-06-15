#ifndef INPUTPROTOCOL_H
#define INPUTPROTOCOL_H

#include "../Socket.h"

#define PRESS_UP 1
#define RELEASE_UP 2
#define PRESS_DOWN 3
#define RELEASE_DOWN 4
#define PRESS_LEFT 5
#define RELEASE_LEFT 6
#define PRESS_RIGHT 7
#define RELEASE_RIGHT 8
#define PRESS_JUMP 9
#define RELEASE_JUMP 10

class InputProtocol {
public:
    static void sendPressUpEvent(Socket& socket);

    static void sendReleaseUpEvent(Socket& socket);

    static void sendPressDownEvent(Socket& socket);

    static void sendReleaseDownEvent(Socket& socket);

    static void sendPressLeftEvent(Socket& socket);

    static void sendReleaseLeftEvent(Socket& socket);

    static void sendPressRightEvent(Socket& socket);

    static void sendReleaseRightEvent(Socket& socket);

    static void sendPressJumpEvent(Socket& socket);

    static void sendReleaseJumpEvent(Socket& socket);
};

#endif //INPUTPROTOCOL_H