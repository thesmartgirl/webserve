#pragma once

#include <cstddef>
#include <string>
#include "HttpRequest.hpp"
#include "HttpError.hpp"

enum class ParseResult {
    Incomplete,
    Complete,
    Error
};

class HttpParser {
public:
    HttpParser();

    ParseResult parse(const std::string& buffer, size_t& consumed, HttpRequest& req, HttpError& err);
    void reset();
};
