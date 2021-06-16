#ifndef SOCKET_H
#define SOCKET_H

#define _POSIX_C_SOURCE 200809L // Habilita getaddrinfo
#include <cstdio> //strerr
#include <cerrno> //errno
#include <sys/socket.h> // socket syscalls
#include <sys/types.h> // socket syscalls
#include <unistd.h> //getaddrinfo y close
#include <netdb.h> //freeaddrinfo y addrlist
#include <string.h> //strerror
#include <utility> //move semantics
#include "Logger.h"

class Socket {
private:
    int fileDescriptor;

    void getaddrinfo(struct addrinfo **addr_list,
                     const char* host, const char* service, int ai_flags, Logger& logger);
public:
    Socket();
    ~Socket();
    explicit Socket(int fileDescriptor);
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);

    int connect(char* ip, char* port, Logger& logger);
    int bind(char* ip, char* port, Logger& logger);
    int listen(int maxQueueLen, Logger& logger);
    Socket accept(Logger& logger);
    int send(const char* buf, size_t len, Logger& logger);
    int receive(char* buf, size_t len, Logger& logger);
    void shutdown(Logger& logger);
    void shutdownRead(Logger& logger);
    void shutdownWrite(Logger& logger);
    void close();
};

#endif //SOCKET_H
