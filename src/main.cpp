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
    std::signal(SIGINT, handleSignal);
    std::signal(SIGTERM, handleSignal);

    std::cout << "Starting webserve non-blocking poll loop" << std::endl;

    while (g_running) {
        const int ready = ::poll(NULL, 0, 100);
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
