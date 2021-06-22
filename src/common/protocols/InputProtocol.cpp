#include "InputProtocol.h"

void InputProtocol::sendPressUpEvent(Socket& socket, Logger& logger){
    char input = PRESS_UP;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona arriba", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseUpEvent(Socket& socket, Logger& logger){
    char input = RELEASE_UP;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se suelta arriba", __FILE__, __LINE__);
}
void InputProtocol::sendPressDownEvent(Socket& socket, Logger& logger){
    char input = PRESS_DOWN;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona abajo", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseDownEvent(Socket& socket, Logger& logger){
    char input = RELEASE_DOWN;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se suelta abajo", __FILE__, __LINE__);
}
void InputProtocol::sendPressLeftEvent(Socket& socket, Logger& logger){
    char input = PRESS_LEFT;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona izquierda", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseLeftEvent(Socket& socket, Logger& logger){
    char input = RELEASE_LEFT;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se suelta izquierda", __FILE__, __LINE__);
}
void InputProtocol::sendPressRightEvent(Socket& socket, Logger& logger){
    char input = PRESS_RIGHT;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona derecha", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseRightEvent(Socket& socket, Logger& logger){
    char input = RELEASE_RIGHT;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se suelta derecha", __FILE__, __LINE__);
}
void InputProtocol::sendPressJumpEvent(Socket& socket, Logger& logger){
    char input = PRESS_JUMP;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona espacio", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseJumpEvent(Socket& socket, Logger& logger){
    char input = RELEASE_JUMP;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se suelta espacio", __FILE__, __LINE__);
}