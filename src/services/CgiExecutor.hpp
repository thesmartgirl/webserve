#pragma once

#include <string>
#include <vector>
#include "http/HttpRequest.hpp"

class CgiExecutor {
public:
    std::string execute(const HttpRequest& req, const std::string& scriptPath,
                        const std::vector<std::string>& envp, int timeoutMs) const;
};
