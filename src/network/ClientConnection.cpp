#include "ClientConnection.hpp"
#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"

ClientConnection::ClientConnection(int fd)
    : _fd(fd), _state(ClientState::NEW_CONNECTION) {}

int ClientConnection::fd() const { return _fd; }

ClientState ClientConnection::state() const { return _state; }

void ClientConnection::setState(ClientState s) { _state = s; }

bool ClientConnection::onReadable() { return true; }

bool ClientConnection::onWritable() { return true; }

HttpRequest& ClientConnection::request() {
    static HttpRequest req;
    return req;
}

HttpResponse& ClientConnection::response() {
    static HttpResponse resp;
    return resp;
}

void ClientConnection::resetForNextRequest() {}
