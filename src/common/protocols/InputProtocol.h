#ifndef INPUTPROTOCOL_H
#define INPUTPROTOCOL_H

#include "../Socket.h"

#define PRESS_UP '1'
#define RELEASE_UP '2'
#define PRESS_DOWN '3'
#define RELEASE_DOWN '4'
#define PRESS_LEFT '5'
#define RELEASE_LEFT '6'
#define PRESS_RIGHT '7'
#define RELEASE_RIGHT '8'
#define PRESS_JUMP '9'
#define RELEASE_JUMP '0'
#define PRESS_INVINCIBILITY 'i'

class InputProtocol {
public:
    static int sendPressUpEvent(Socket& socket, Logger& logger);

    static int sendReleaseUpEvent(Socket& socket, Logger& logger);

    static int sendPressDownEvent(Socket& socket, Logger& logger);

    static int sendReleaseDownEvent(Socket& socket, Logger& logger);

    static int sendPressLeftEvent(Socket& socket, Logger& logger);

    static int sendReleaseLeftEvent(Socket& socket, Logger& logger);

    static int sendPressRightEvent(Socket& socket, Logger& logger);

    static int sendReleaseRightEvent(Socket& socket, Logger& logger);

    static int sendPressJumpEvent(Socket& socket, Logger& logger);

    static int sendReleaseJumpEvent(Socket& socket, Logger& logger);

    static int sendInvincibility(Socket& socket, Logger& logger);
};

#endif //INPUTPROTOCOL_H