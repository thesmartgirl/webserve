#include "HttpParser.hpp"

HttpParser::HttpParser() {}

ParseResult HttpParser::parse(const std::string& buffer, size_t& consumed, HttpRequest& req, HttpError& err) {
    (void)buffer;
    (void)consumed;
    (void)req;
    (void)err;
    return ParseResult::Incomplete;
}

void HttpParser::reset() {}
