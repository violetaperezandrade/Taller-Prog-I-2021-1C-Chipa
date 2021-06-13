#include "Client.h"

Client::Client(char *ip, char *port,Logger& logger) : skt(),logger(logger),view(logger,Config& config),ip(ip),port(port){}

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

    connect(ip,port);
    Login login(logger, skt);
    login.runLoginWindow();

    ClientInput input(skt);
    input.run();

    Processor processor(entities,skt);
    processor.readEntities();

    processor.joinThread();



}