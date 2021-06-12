#include "InputProtocol.h"

void InputProtocol::sendPressUpEvent(Socket socket){
    char input = 1;
    socket.send(&input, 1);
}
void InputProtocol::sendReleaseUpEvent(Socket socket){
    char input = 2;
    socket.send(&input, 1);
}
void InputProtocol::sendPressDownEvent(Socket socket){
    char input = 3;
    socket.send(&input, 1);
}
void InputProtocol::sendReleaseDownEvent(Socket socket){
    char input = 4;
    socket.send(&input, 1);
}
void InputProtocol::sendPressLeftEvent(Socket socket){
    char input = 5;
    socket.send(&input, 1);
}
void InputProtocol::sendReleaseLeftEvent(Socket socket){
    char input = 6;
    socket.send(&input, 1);
}
void InputProtocol::sendPressRightEvent(Socket socket){
    char input = 7;
    socket.send(&input, 1);
}
void InputProtocol::sendReleaseRightEvent(Socket socket){
    char input = 8;
    socket.send(&input, 1);
}
void InputProtocol::sendPressJumpEvent(Socket socket){
    char input = 9;
    socket.send(&input, 1);
}
void InputProtocol::sendReleaseJumpEvent(Socket socket){
    char input = 10;
    socket.send(&input, 1);
}