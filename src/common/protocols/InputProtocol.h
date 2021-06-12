#ifndef INPUTPROTOCOL_H
#define INPUTPROTOCOL_H

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
    void sendPressUpEvent(Socket socket);

    void sendReleaseUpEvent(Socket socket);

    void sendPressDownEvent(Socket socket);

    void sendReleaseDownEvent(Socket socket);

    void sendPressLeftEvent(Socket socket);

    void sendReleaseLeftEvent(Socket socket);

    void sendPressRightEvent(Socket socket);

    void sendReleaseRightEvent(Socket socket);

    void sendPressJumpEvent(Socket socket);

    void sendReleaseJumpEvent(Socket socket);
};

#endif //INPUTPROTOCOL_H