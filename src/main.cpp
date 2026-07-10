#include <cerrno>
#include <csignal>
#include <cstring>
#include <iostream>
#include <poll.h>

namespace {
volatile std::sig_atomic_t g_running = 1;

void handleSignal(int) {
    g_running = 0;
}
} // namespace

int main() {
    if (std::signal(SIGINT, handleSignal) == SIG_ERR || std::signal(SIGTERM, handleSignal) == SIG_ERR) {
        std::cerr << "failed to register signal handlers" << std::endl;
        return 1;
    }

    std::cout << "Starting webserve non-blocking poll loop" << std::endl;

    while (g_running) {
        const int ready = ::poll(nullptr, 0, 100);
        if (ready < 0) {
            if (errno == EINTR) {
                continue;
            }
            std::cerr << "poll failed: " << std::strerror(errno) << std::endl;
            return 1;
        }
    }

    return 0;
}
