#include "InputProtocol.h"

void InputProtocol::sendPressUpEvent(Socket& socket, Logger& logger){
    char input = 1;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona arriba", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseUpEvent(Socket& socket, Logger& logger){
    char input = 2;
    socket.send(&input, 1, logger);
}
void InputProtocol::sendPressDownEvent(Socket& socket, Logger& logger){
    char input = 3;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona abajo", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseDownEvent(Socket& socket, Logger& logger){
    char input = 4;
    socket.send(&input, 1, logger);
}
void InputProtocol::sendPressLeftEvent(Socket& socket, Logger& logger){
    char input = 5;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona izquierda", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseLeftEvent(Socket& socket, Logger& logger){
    char input = 6;
    socket.send(&input, 1, logger);
}
void InputProtocol::sendPressRightEvent(Socket& socket, Logger& logger){
    char input = 7;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona derecha", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseRightEvent(Socket& socket, Logger& logger){
    char input = 8;
    socket.send(&input, 1, logger);
}
void InputProtocol::sendPressJumpEvent(Socket& socket, Logger& logger){
    char input = 9;
    socket.send(&input, 1, logger);
    logger.superDebugMsg("Se presiona espacio", __FILE__, __LINE__);
}
void InputProtocol::sendReleaseJumpEvent(Socket& socket, Logger& logger){
    char input = 10;
    socket.send(&input, 1, logger);
}