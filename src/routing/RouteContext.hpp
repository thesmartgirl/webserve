#pragma once

#include "config/ConfigModel.hpp"
#include "routing/RouteMatch.hpp"

struct RouteContext {
    const ServerConfig* server;
    RouteMatch match;
};
