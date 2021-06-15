#include "Socket.h"
#include <iostream>

#include "Logger.h"

Socket::Socket() : fileDescriptor(-1) {}

Socket::Socket(int fileDescriptor) : fileDescriptor(fileDescriptor) {}

Socket::Socket(Socket&& other) {
    this->fileDescriptor = std::move(other.fileDescriptor);
    other.fileDescriptor = -1;
}

Socket& Socket::operator=(Socket&& other) {
    this->fileDescriptor = std::move(other.fileDescriptor);
    other.fileDescriptor = -1;
    return *this;
}

void Socket::getaddrinfo(struct addrinfo **addr_list,
                         const char* host, const char* service, int ai_flags){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = ai_flags;
    hints.ai_socktype = SOCK_STREAM;

    int status = ::getaddrinfo(host, service, &hints, addr_list);
    if (status != 0) {
        freeaddrinfo(*addr_list);
        std::string str(strerror(errno));
        logger.debugMsg("Getaddrinfo error: " + str, __FILE__, __LINE__);
    }
}

int Socket::connect(char* ip, char* port){
    struct addrinfo *addressList, *ptr;

    getaddrinfo(addressList,ip,port,0);

    status = 0;

    for(ptr = addressList; ptr; ptr = ptr->ai_next){
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(fileDescriptor < 0) {
            std::string str(strerror(errno));
            logger.debugMsg("Socket error: " + str, __FILE__, __LINE__);
        }
        else{
            status = connect(fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
            if(status < 0){
                std::string str(strerror(errno));
                logger.debugMsg("Connect error: " + str, __FILE__, __LINE__);
                socketDestroy();
            }
        }
    }
    freeaddrinfo(addrList);
    return status;
}

int Socket::bind(char* ip, char* port){
    struct addrinfo *addressList, *ptr;

    getaddrinfo(addressList,ip,port,AI_PASSIVE);

    int status = 0;
    int val = 1;

    for(ptr = addressList; ptr ; ptr = ptr->ai_next){
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(fileDescriptor < 0) {
            std::string str(strerror(errno));
            logger.debugMsg("Socket error: " + str, __FILE__, __LINE__);
        }
        else{
            setsockopt(fileDescriptor,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
            status = bind(fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
            if(status < 0){
                std::string str(strerror(errno));
                logger.debugMsg("Bind error: " + str, __FILE__, __LINE__);
                socketDestroy();
            }
        }
    }
    freeaddrinfo(addressList);
    return status;
}

int Socket::listen(int maxQueueLen){
    int status = 0;
    status = listen(fileDescriptor, maxQueueLen);
    if(status < 0 ) {
        std::string str(strerror(errno));
        logger.debugMsg("Listen error: " + str, __FILE__, __LINE__);;
    }
    return status;
}

Socket Socket::accept(){
    int newFileDescriptor = accept(fileDescriptor,NULL,NULL);
    if(newFileDescriptor< 0) {
        std::string str(strerror(errno));
        logger.debugMsg("Accept error: " + str, __FILE__, __LINE__);
    }
    return Socket(newFileDescriptor);
}

int Socket::send(const char* buf, size_t len){
    int totalBytesSent = 0;
    int bytesSent = 0;
    for(; bytesSent < len;){
        bytesSent = send(fileDescriptor,&(buf[totalBytesSent]),len - totalBytesSent,MSG_NOSIGNAL);
        if(bytesSent < 0) {
            std::string str(strerror(errno));
            logger.debugMsg("Send error: " + str, __FILE__, __LINE__);
        }
        else{
            totalBytesSent += bytesSent;
        }
    }
    return totalBytesSent;
}

int Socket::receive(char* buf, size_t len){
    int totalBytesRcvd = 0;
    int bytesRcvd = 0;
    while(bytesRcvd < len){
        bytesRcvd = recv(fileDescriptor,&(buf[totalBytesRcvd]),len - totalBytesRcvd,0);
        if(bytesRcvd < 0){
            std::string str(strerror(errno));
            logger.debugMsg("Receive error: " + str, __FILE__, __LINE__);
            break;
        }
        if(bytesRcvd == 0) break;

        totalBytesRcvd += bytesRcvd;
    }
    return totalBytesRcvd;
}

void Socket::shutdown(){
    if (::shutdown(fileDescriptor, SHUT_RDWR) != 0){
        std::string str(strerror(errno));
        logger.debugMsg("ShutdownRDWR error: " + str, __FILE__, __LINE__);
    }
}

void Socket::shutdownRead(){
    if (::shutdown(fileDescriptor, SHUT_RD) != 0){
        std::string str(strerror(errno));
        logger.debugMsg("ShutdownRD error: " + str, __FILE__, __LINE__);
    }
}

void Socket::shutdownWrite(){
    if (::shutdown(fileDescriptor, SHUT_WR) != 0){
        std::string str(strerror(errno));
        logger.debugMsg("ShutdownWR error: " + str, __FILE__, __LINE__);
    }
}


void Socket::close(){
    if (::close(fileDescriptor) != 0){
        std::string str(strerror(errno));
        logger.debugMsg("Closing error: " + str, __FILE__, __LINE__);
    }
}

Socket::~Socket(){
    if (fileDescriptor == -1){
        return;
    }
    close();
}
