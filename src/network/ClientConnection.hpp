#pragma once

#include <string>

class HttpRequest;
class HttpResponse;

enum class ClientState {
    NEW_CONNECTION,
    READING_HEADERS,
    READING_BODY,
    PROCESSING,
    WRITING_RESPONSE,
    IDLE_KEEP_ALIVE,
    CLOSED,
    ERROR
};

class ClientConnection {
public:
    explicit ClientConnection(int fd);

    int fd() const;
    ClientState state() const;
    void setState(ClientState s);

    bool onReadable();
    bool onWritable();

    HttpRequest& request();
    HttpResponse& response();

    void resetForNextRequest();

    bool needsWrite() const;

private:
    int _fd;
    ClientState _state;
    std::string _inBuffer;
    std::string _outBuffer;
    size_t _bytesSent;
};
