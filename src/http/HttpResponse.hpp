#pragma once

#include <map>
#include <string>

class HttpResponse {
public:
    HttpResponse();

    int statusCode;
    std::string reasonPhrase;
    std::map<std::string, std::string> headers;
    std::string body;

    std::string serialize() const;
};
