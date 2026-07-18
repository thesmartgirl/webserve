#include "Server.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

Server::Server() : _listenFd(-1), _port(8080), _backlog(128) {}

Server::Server(const char* host, int port, int backlog)
    : _listenFd(-1), _port(port), _backlog(backlog) {
    (void)host;
}

Server::~Server() {
    if (_listenFd >= 0) {
        close(_listenFd);
        _listenFd = -1;
    }
}

static bool setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return false;
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) return false;
    return true;
}

bool Server::start() {
    _listenFd = socket(AF_INET, SOCK_STREAM, 0);
    if (_listenFd < 0) return false;

    int opt = 1;
    setsockopt(_listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (!setNonBlocking(_listenFd)) return false;

    sockaddr_in addr;
    std::memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(static_cast<uint16_t>(_port));

    if (bind(_listenFd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        return false;
    }

    if (listen(_listenFd, _backlog) < 0) {
        return false;
    }

    return true;
}

int Server::listenFd() const {
    return _listenFd;
}

int Server::port() const {
    return _port;
}
