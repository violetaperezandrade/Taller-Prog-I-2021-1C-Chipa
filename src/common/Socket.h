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

class Socket {
private:
    int fileDescriptor;

    void getaddrinfo(struct addrinfo **addr_list,
                     const char* host, const char* service, int ai_flags);

public:

    Socket();
    ~Socket();
    explicit Socket(int fileDescriptor);
    Socket(Socket&& other);
    Socket& operator=(Socket&& other);
    int connect(char* ip, char* port);
    int bind(char* ip, char* port);
    int listen(int maxQueueLen);
    Socket accept();
    int send(const char* buf, size_t len);
    int receive(char* buf, size_t len);
    void shutdown();
    void shutdownRead();
    void shutdownWrite();
    void close();

};

#endif //SOCKET_H
