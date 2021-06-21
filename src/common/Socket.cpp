#include "Socket.h"

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
                         const char* host, const char* service, int ai_flags, Logger& logger){

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_flags = ai_flags;
    hints.ai_socktype = SOCK_STREAM;

    int status = ::getaddrinfo(host, service, &hints, addr_list);
    if (status != 0) {
        freeaddrinfo(*addr_list);
        std::string str(strerror(errno));
        logger.errorMsg("Getaddrinfo error: " + str, __FILE__, __LINE__);
    }
}

int Socket::connect(char* ip, char* port, Logger& logger){
    struct addrinfo *addressList, *ptr;

    getaddrinfo(&addressList,ip,port,0,logger);

    int status = 0;

    for(ptr = addressList; ptr; ptr = ptr->ai_next){
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(fileDescriptor < 0) {
            std::string str(strerror(errno));
            logger.errorMsg("Socket error: " + str, __FILE__, __LINE__);
        }
        else{
            status = ::connect(fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
            if(status < 0){
                std::string str(strerror(errno));
                logger.errorMsg("Connect error: " + str, __FILE__, __LINE__);
                close();
            }
        }
    }
    freeaddrinfo(addressList);
    logger.infoMsg("Connected with fd: " + std::to_string(fileDescriptor) , __FILE__, __LINE__);
    return status;
}

int Socket::bind(char* ip, char* port, Logger& logger){
    struct addrinfo *addressList, *ptr;

    getaddrinfo(&addressList,ip,port,AI_PASSIVE, logger);

    int status = 0;
    int val = 1;

    for(ptr = addressList; ptr ; ptr = ptr->ai_next){
        fileDescriptor = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if(fileDescriptor < 0) {
            std::string str(strerror(errno));
            logger.errorMsg("Socket error: " + str, __FILE__, __LINE__);
        }
        else{
            setsockopt(fileDescriptor,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));
            status = ::bind(fileDescriptor, ptr->ai_addr, ptr->ai_addrlen);
            if(status < 0){
                std::string str(strerror(errno));
                logger.errorMsg("Bind error: " + str, __FILE__, __LINE__);
                close();
            }
        }
    }
    freeaddrinfo(addressList);
    logger.infoMsg("Binded with fd: " + std::to_string(fileDescriptor) , __FILE__, __LINE__);
    return status;
}

int Socket::listen(int maxQueueLen, Logger& logger){
    int status = 0;
    status = ::listen(fileDescriptor, maxQueueLen);
    if(status < 0 ) {
        std::string str(strerror(errno));
        logger.errorMsg("Listen error: " + str, __FILE__, __LINE__);
    }
    logger.infoMsg("Listening with fd: " + std::to_string(fileDescriptor) , __FILE__, __LINE__);
    return status;
}

Socket Socket::accept(Logger& logger){
    int newFileDescriptor = ::accept(fileDescriptor,NULL,NULL);
    if(newFileDescriptor < 0) {
        std::string str(strerror(errno));
        logger.errorMsg("Accept error: " + str, __FILE__, __LINE__);
    }
    logger.infoMsg("Accepting new fd: " + std::to_string(newFileDescriptor) , __FILE__, __LINE__);
    return Socket(newFileDescriptor);
}

int Socket::send(const char* buf, size_t len, Logger& logger){
    int totalBytesSent = 0;
    int bytesSent = 0;
    for(; bytesSent < len;){
        bytesSent = ::send(fileDescriptor,&(buf[totalBytesSent]),len - totalBytesSent,MSG_NOSIGNAL);
        std::string buff(buf,len);
        std::string br = std::to_string(bytesSent);
        logger.superDebugMsg("Send: " + buff + " bytes sent: " + br , __FILE__, __LINE__);
        if(bytesSent < 0) {
            std::string str(strerror(errno));
            logger.errorMsg("Send error: " + str, __FILE__, __LINE__);
        }
        else{
            totalBytesSent += bytesSent;
        }
    }
    return totalBytesSent;
}

int Socket::receive(char* buf, size_t len, Logger& logger){
    int totalBytesRcvd = 0;
    int bytesRcvd = 0;
    while(bytesRcvd < len){
        bytesRcvd = recv(fileDescriptor,&(buf[totalBytesRcvd]),len - totalBytesRcvd,0);
        std::string buff(buf,len);
        std::string br = std::to_string(bytesRcvd);
        logger.superDebugMsg("Receive: " + buff + " bytes recv: " + br , __FILE__, __LINE__);
        if(bytesRcvd < 0){
            std::string str(strerror(errno));
            logger.errorMsg("Receive error: " + str, __FILE__, __LINE__);
            break;
        }
        if(bytesRcvd == 0) break;

        totalBytesRcvd += bytesRcvd;
    }
    return totalBytesRcvd;
}

void Socket::shutdown(Logger& logger){
    if(fileDescriptor == -1) return;
    if (::shutdown(fileDescriptor, SHUT_RDWR) != 0){
        std::string str(strerror(errno));
        logger.errorMsg("ShutdownRDWR error: " + str, __FILE__, __LINE__);
    }
    close();
    logger.infoMsg("Shutdown and close now fd is: " + std::to_string(fileDescriptor) , __FILE__, __LINE__);
}

void Socket::shutdownRead(Logger& logger){
    if (::shutdown(fileDescriptor, SHUT_RD) != 0){
        std::string str(strerror(errno));
        logger.errorMsg("ShutdownRD error: " + str, __FILE__, __LINE__);
    }
    logger.infoMsg("ShutdownRead now fd is: " + std::to_string(fileDescriptor) , __FILE__, __LINE__);
}

void Socket::shutdownWrite(Logger& logger){
    if (::shutdown(fileDescriptor, SHUT_WR) != 0){
        std::string str(strerror(errno));
        logger.errorMsg("ShutdownWR error: " + str, __FILE__, __LINE__);
    }
    logger.infoMsg("ShutdownWrite now fd is: " + std::to_string(fileDescriptor) , __FILE__, __LINE__);
}


void Socket::close(){
    if(fileDescriptor != -1){
        if (::close(fileDescriptor) != 0){
            return;
        }
        fileDescriptor = -1;
    }
}

Socket::~Socket(){
    if (fileDescriptor == -1){
        return;
    }
    close();
}
