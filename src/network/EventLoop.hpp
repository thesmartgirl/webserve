#pragma once

#include <map>
#include <vector>

class Server;
class ServerManager;

class EventLoop {
public:
    explicit EventLoop(ServerManager& manager);
    void run();

private:
    ServerManager& _manager;
};
