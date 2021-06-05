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
    void sendEvent(BlockingQueue<char>& queue, SDL_event& e);
    // no le pongo readEvent para en el server directamente usar un switch con
    // el char que me llega
};

#endif //INPUTPROTOCOL_H