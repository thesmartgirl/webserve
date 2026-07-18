#include "HttpResponse.hpp"
#include <sstream>

HttpResponse::HttpResponse() : statusCode(200), reasonPhrase("OK"), headers(), body() {}

std::string HttpResponse::serialize() const {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << statusCode << " " << reasonPhrase << "\r\n";
    for (std::map<std::string, std::string>::const_iterator it = headers.begin(); it != headers.end(); ++it) {
        oss << it->first << ": " << it->second << "\r\n";
    }
    oss << "\r\n";
    oss << body;
    return oss.str();
}
