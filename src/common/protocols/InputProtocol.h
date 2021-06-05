#ifndef INPUTPROTOCOL_H
#define INPUTPROTOCOL_H

class InputProtocol {
public:
    void sendEvent(BlockingQueue<char>& queue, SDL_event& e);
    // no le pongo readEvent para en el server directamente usar un switch con
    // el char que me llega
};

#endif //INPUTPROTOCOL_H