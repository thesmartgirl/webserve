#pragma once

#include <string>
#include "http/HttpResponse.hpp"

class CgiResponseParser {
public:
    HttpResponse parse(const std::string& rawCgiOutput) const;
};
