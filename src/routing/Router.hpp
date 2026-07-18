#pragma once

#include "config/ConfigModel.hpp"
#include "http/HttpRequest.hpp"
#include "RouteMatch.hpp"

class Router {
public:
    explicit Router(const ConfigModel& config);
    RouteMatch resolve(const ServerConfig& server, const HttpRequest& request) const;
};
