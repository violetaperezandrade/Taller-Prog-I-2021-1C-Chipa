#include "Client.h"

Client::Client(char *ip, char *port, Logger& logger, Config& config) : skt(), logger(logger), entities(), ip(ip), port(port), config(config){}

Client::~Client(){
    skt.shutdown();
}

int Client::connect(char* ip, char* port){
    return skt.connect(ip,port);
}

int Client::send(const char* msg, size_t len){
    return skt.send(msg, len);
}

int Client::recv(char* msg, size_t len){
    return skt.receive(msg,len);
}

void Client::run(){

    Login login(logger, skt);
    int status = login.runLoginWindow(ip,port);
    if(status < 0) return;

    Input* input = new Input(skt);
    input->start();

    Monitor monitor;
    Processor* processor = new Processor(monitor, skt);
    processor->start();

    View view(monitor, logger, config);

    input->stop();
    processor->stop();

    processor->join();
    input->join();

    delete input;
    delete processor;
}