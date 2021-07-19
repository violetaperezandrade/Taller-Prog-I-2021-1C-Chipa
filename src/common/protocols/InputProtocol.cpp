#include "InputProtocol.h"

int InputProtocol::sendPressUpEvent(Socket& socket, Logger& logger){
    char input = PRESS_UP;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se presiona arriba", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendReleaseUpEvent(Socket& socket, Logger& logger){
    char input = RELEASE_UP;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se suelta arriba", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendPressDownEvent(Socket& socket, Logger& logger){
    char input = PRESS_DOWN;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se presiona abajo", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendReleaseDownEvent(Socket& socket, Logger& logger) {
    char input = RELEASE_DOWN;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se suelta abajo", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendPressLeftEvent(Socket& socket, Logger& logger) {
    char input = PRESS_LEFT;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se presiona izquierda", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendReleaseLeftEvent(Socket& socket, Logger& logger){
    char input = RELEASE_LEFT;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se suelta izquierda", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendPressRightEvent(Socket& socket, Logger& logger){
    char input = PRESS_RIGHT;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se presiona derecha", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendReleaseRightEvent(Socket& socket, Logger& logger){
    char input = RELEASE_RIGHT;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se suelta derecha", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendPressJumpEvent(Socket& socket, Logger& logger){
    char input = PRESS_JUMP;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se presiona espacio", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendReleaseJumpEvent(Socket& socket, Logger& logger){
    char input = RELEASE_JUMP;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se suelta espacio", __FILE__, __LINE__);
    return success;
}

int InputProtocol::sendInvincibility(Socket& socket, Logger& logger){
    char input = PRESS_INVINCIBILITY;
    int success = socket.send(&input, 1, logger);
    if (success <= 0) logger.debugMsg("Sending event failed", __FILE__, __LINE__);
    else logger.superDebugMsg("Se suelta espacio", __FILE__, __LINE__);
    return success;
}