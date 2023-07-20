#include <exception>
#include "udp.h"

#if defined(_WIN32)
#include <winsock2.h>
#include <Windows.h>
#elif defined(__linux__)
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

Udp::Udp(char const* addr, std::uint16_t port) {
    _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (_sock == -1) {
        throw std::exception();
    }

    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);
    address.sin_family = AF_INET;   // IPv4

    int status = bind(_sock, (sockaddr*)&address, sizeof(address));
    if (status == -1) {
        throw std::exception();
    }

#if defined(_WIN32)
    DWORD read_timeout = 10;
    setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, (char*) & read_timeout, sizeof read_timeout);
#elif defined(__linux__)
    // Ставим таймаут на вызов recvfrom. Иначе если данных ожидающих в буфере на приём не будет программа зависнет
    // пока не получит хотябы один байт от другого компьютера
    // https://stackoverflow.com/questions/15941005/making-recvfrom-function-non-blocking
    struct timeval read_timeout;
    read_timeout.tv_sec = 0;
    read_timeout.tv_usec = 10;
    setsockopt(_sock, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
#endif
}

Udp::~Udp() {
    #if defined(_WIN32)
        closesocket(_sock);
    #elif defined(__linux__)
        close(_sock);
    #endif
}

int Udp::recv(char const* addr, std::uint16_t port, void* buf, int length) {
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);
    address.sin_family = AF_INET;   // IPv4

#if defined(_WIN32)
    int addr_len = sizeof(address);
#elif defined(__linux__)
    socklen_t addr_len = sizeof(address);
#endif

    return recvfrom(_sock, (char*)buf, length, 0, (sockaddr*)&address, &addr_len);
}

int Udp::send(char const* addr, std::uint16_t port, void const* buf, int length) {
    sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_addr.s_addr = inet_addr(addr);
    address.sin_port = htons(port);
    address.sin_family = AF_INET;   // IPv4

#if defined(_WIN32)
    int addr_len = sizeof(address);
#elif defined(__linux__)
    socklen_t addr_len = sizeof(address);
#endif

    return sendto(_sock, (char const*)buf, length, 0, (sockaddr*)&address, addr_len);
}
