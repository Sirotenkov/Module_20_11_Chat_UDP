#pragma once
#include <cstdint>  // uint*
#include <cstring>

#if defined(_WIN32)
#include <winsock2.h>
#include <Windows.h>
#elif defined(__linux__)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

class Udp
{
    public:
        Udp(char const* addr, std::uint16_t port);
        ~Udp();
        int recv(char const* addr, std::uint16_t port, void* buf, int length);
        int send(char const* addr, std::uint16_t port, void const* buf, int length);

    private:
        int _sock;
};
