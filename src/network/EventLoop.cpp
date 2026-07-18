#include "EventLoop.hpp"

#include <poll.h>
#include <vector>

#include "ServerManager.hpp"
#include "Server.hpp"
#include "ClientConnection.hpp"

EventLoop::EventLoop(ServerManager& manager) : _manager(manager) {}

void EventLoop::run() {
    while (true) {
        std::vector<pollfd> pfds;

        const std::vector<Server>& servers = _manager.servers();
        for (size_t i = 0; i < servers.size(); ++i) {
            pollfd p;
            p.fd = servers[i].listenFd();
            p.events = POLLIN;
            p.revents = 0;
            pfds.push_back(p);
        }

        std::map<int, ClientConnection>& clients = _manager.clients();
        for (std::map<int, ClientConnection>::iterator it = clients.begin(); it != clients.end(); ++it) {
            pollfd p;
            p.fd = it->first;
            p.events = POLLIN;
            if (it->second.needsWrite()) p.events |= POLLOUT;
            p.revents = 0;
            pfds.push_back(p);
        }

        int ready = poll(&pfds[0], static_cast<nfds_t>(pfds.size()), 1000);
        if (ready <= 0) {
            continue;
        }

        size_t serverCount = servers.size();
        for (size_t i = 0; i < pfds.size(); ++i) {
            if (!(pfds[i].revents & (POLLIN | POLLOUT | POLLERR | POLLHUP))) continue;

            int fd = pfds[i].fd;
            if (i < serverCount) {
                if (pfds[i].revents & POLLIN) {
                    _manager.acceptClient(fd);
                }
                continue;
            }

            if (pfds[i].revents & (POLLERR | POLLHUP)) {
                _manager.closeClient(fd);
                continue;
            }

            if (pfds[i].revents & POLLIN) {
                _manager.handleClientReadable(fd);
            }
            if (pfds[i].revents & POLLOUT) {
                _manager.handleClientWritable(fd);
            }
        }
    }
}
