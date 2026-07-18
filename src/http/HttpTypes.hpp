#pragma once

#include <string>

enum class HttpMethod {
    GET,
    POST,
    DELETE_,
    UNKNOWN
};

inline std::string toString(HttpMethod method) {
    switch (method) {
        case HttpMethod::GET: return "GET";
        case HttpMethod::POST: return "POST";
        case HttpMethod::DELETE_: return "DELETE";
        default: return "UNKNOWN";
    }
}
