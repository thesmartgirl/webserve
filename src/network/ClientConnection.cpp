#include "ClientConnection.hpp"

#include <sys/socket.h>
#include <unistd.h>

#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"

ClientConnection::ClientConnection(int fd)
    : _fd(fd), _state(ClientState::NEW_CONNECTION), _bytesSent(0) {}

int ClientConnection::fd() const { return _fd; }

ClientState ClientConnection::state() const { return _state; }

void ClientConnection::setState(ClientState s) { _state = s; }

bool ClientConnection::onReadable() {
    char buf[4096];
    ssize_t n = recv(_fd, buf, sizeof(buf), 0);
    if (n <= 0) {
        return false;
    }

    _inBuffer.append(buf, static_cast<size_t>(n));

    if (_inBuffer.find("\r\n\r\n") != std::string::npos) {
        _outBuffer =
            "HTTP/1.1 200 OK\r\n"
            "Content-Length: 5\r\n"
            "Connection: close\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "Hello";
        _bytesSent = 0;
        _state = ClientState::WRITING_RESPONSE;
    } else {
        _state = ClientState::READING_HEADERS;
    }

    return true;
}

bool ClientConnection::onWritable() {
    if (_outBuffer.empty()) return true;

    ssize_t n = send(_fd, _outBuffer.data() + _bytesSent, _outBuffer.size() - _bytesSent, 0);
    if (n < 0) {
        return false;
    }

    _bytesSent += static_cast<size_t>(n);
    if (_bytesSent >= _outBuffer.size()) {
        return false;
    }

    return true;
}

HttpRequest& ClientConnection::request() {
    static HttpRequest req;
    return req;
}

HttpResponse& ClientConnection::response() {
    static HttpResponse resp;
    return resp;
}

void ClientConnection::resetForNextRequest() {
    _inBuffer.clear();
    _outBuffer.clear();
    _bytesSent = 0;
    _state = ClientState::READING_HEADERS;
}

bool ClientConnection::needsWrite() const {
    return !_outBuffer.empty() && _state == ClientState::WRITING_RESPONSE;
}
