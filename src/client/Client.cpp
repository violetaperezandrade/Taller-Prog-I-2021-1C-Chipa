#include "Client.h"

Client::Client(char *ip, char *port,Logger& logger) : skt(),logger(logger),ip(ip),port(port){}

Client::~Client(){
    skt.shutdown();
}

int Client::connect(char* ip, char* port){
    return skt.connect(ip,port);
}

int Client::send(const char* msg, size_t len){
    return skt.send(msg, len);
}

int Cliend::recv(char* msg, size_t len){
    return skt.receive(msg,len);
}

void Client::run(){

    Login login(logger, skt);
    login.runLoginWindow();

    ClientInput* input = new ClientInput(skt);
    input->start();

    Monitor monitor(entities);
    Processor* processor = new Processor(monitor, skt);
    processor->start();

    View view(monitor,logger,config);

    input->stop();
    processor->stop();

    processor->join();
    input->join();

    delete input;
    delete processor;
}