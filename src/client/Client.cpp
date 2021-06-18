#include "Client.h"

Client::Client(char *ip, char *port, Logger& logger, Config& config) : skt(), logger(logger), entities(), ip(ip), port(port), config(config){}

Client::~Client(){
    skt.shutdown(logger);
}

int Client::connect(char* ip, char* port){
    return skt.connect(ip,port,logger);
}

int Client::send(const char* msg, size_t len){
    return skt.send(msg, len,logger);
}

int Client::recv(char* msg, size_t len){
    return skt.receive(msg,len,logger);
}

void Client::run(){

    logger.infoMsg("Se inicia un cliente",__FILE__,__LINE__);

    Login login(logger, skt);
    int status = login.runLoginWindow(ip,port);
    if(status < 0){
        logger.errorMsg("Algo salio mal en ventana de login",__FILE__,__LINE__);
        return;
    }

    Input* input = new Input(skt,logger);

    Monitor monitor(logger);
    Processor* processor = new Processor(monitor, skt,logger);

    logger.debugMsg("Se lanza thread INPUT",__FILE__,__LINE__);
    logger.debugMsg("Se lanza thread PROCESSOR",__FILE__,__LINE__);
    input->start();
    processor->start();

    View view(monitor, logger, config);
    view.run();

    input->stop();
    processor->stop();

    processor->join();
    input->join();

    delete input;
    delete processor;
}