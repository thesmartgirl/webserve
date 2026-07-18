#include "ServerManager.hpp"

#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include "network/EventLoop.hpp"
#include "utils/Logger.hpp"

ServerManager::ServerManager() : _servers(), _clients(), _eventLoop(0) {}

ServerManager::~ServerManager() {
    delete _eventLoop;
    for (std::map<int, ClientConnection>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
        close(it->first);
    }
}

void ServerManager::initialize(const char* configPath) {
    (void)configPath;

    Server s("0.0.0.0", 8080, 128);
    if (!s.start()) {
        Logger::error("Failed to start listening socket on port 8080");
        return;
    }
    _servers.push_back(s);

    if (!_eventLoop) _eventLoop = new EventLoop(*this);

    Logger::info("Listening on 0.0.0.0:8080");
}

void ServerManager::run() {
    if (!_eventLoop) {
        Logger::error("EventLoop not initialized");
        return;
    }
    _eventLoop->run();
}

const std::vector<Server>& ServerManager::servers() const { return _servers; }

std::map<int, ClientConnection>& ServerManager::clients() { return _clients; }

static bool setNonBlockingFd(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags < 0) return false;
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0) return false;
    return true;
}

void ServerManager::acceptClient(int listenFd) {
    while (true) {
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int clientFd = accept(listenFd, reinterpret_cast<sockaddr*>(&addr), &len);
        if (clientFd < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) break;
            return;
        }

        if (!setNonBlockingFd(clientFd)) {
            close(clientFd);
            continue;
        }

        _clients.insert(std::make_pair(clientFd, ClientConnection(clientFd)));
    }
}

void ServerManager::handleClientReadable(int clientFd) {
    std::map<int, ClientConnection>::iterator it = _clients.find(clientFd);
    if (it == _clients.end()) return;

    if (!it->second.onReadable()) {
        closeClient(clientFd);
    }
}

void ServerManager::handleClientWritable(int clientFd) {
    std::map<int, ClientConnection>::iterator it = _clients.find(clientFd);
    if (it == _clients.end()) return;

    if (!it->second.onWritable()) {
        closeClient(clientFd);
    }
}

void ServerManager::closeClient(int clientFd) {
    std::map<int, ClientConnection>::iterator it = _clients.find(clientFd);
    if (it == _clients.end()) return;
    close(clientFd);
    _clients.erase(it);
}
