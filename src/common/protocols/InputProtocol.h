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
    static void sendPressUpEvent(Socket& socket, Logger& logger);

    static void sendReleaseUpEvent(Socket& socket, Logger& logger);

    static void sendPressDownEvent(Socket& socket, Logger& logger);

    static void sendReleaseDownEvent(Socket& socket, Logger& logger);

    static void sendPressLeftEvent(Socket& socket, Logger& logger);

    static void sendReleaseLeftEvent(Socket& socket, Logger& logger);

    static void sendPressRightEvent(Socket& socket, Logger& logger);

    static void sendReleaseRightEvent(Socket& socket, Logger& logger);

    static void sendPressJumpEvent(Socket& socket, Logger& logger);

    static void sendReleaseJumpEvent(Socket& socket, Logger& logger);
};

#endif //INPUTPROTOCOL_H