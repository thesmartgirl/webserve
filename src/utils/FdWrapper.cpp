#include "FdWrapper.hpp"
#include <unistd.h>

FdWrapper::FdWrapper(int fd) : _fd(fd) {}

FdWrapper::~FdWrapper() {
    if (_fd >= 0) {
        close(_fd);
    }
}

int FdWrapper::get() const { return _fd; }

int FdWrapper::release() {
    int out = _fd;
    _fd = -1;
    return out;
}

void FdWrapper::reset(int newFd) {
    if (_fd >= 0) {
        close(_fd);
    }
    _fd = newFd;
}
