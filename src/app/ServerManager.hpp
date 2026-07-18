#pragma once

#include <map>
#include <vector>

#include "network/Server.hpp"
#include "network/ClientConnection.hpp"

class EventLoop;

class ServerManager {
public:
    ServerManager();
    ~ServerManager();

    void initialize(const char* configPath);
    void run();

    const std::vector<Server>& servers() const;
    std::map<int, ClientConnection>& clients();

    void acceptClient(int listenFd);
    void handleClientReadable(int clientFd);
    void handleClientWritable(int clientFd);
    void closeClient(int clientFd);

private:
    std::vector<Server> _servers;
    std::map<int, ClientConnection> _clients;
    EventLoop* _eventLoop;
};
