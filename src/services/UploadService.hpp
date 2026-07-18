#pragma once

#include <string>
#include "http/HttpRequest.hpp"

class UploadService {
public:
    std::string store(const HttpRequest& req, const std::string& uploadDir) const;
};
