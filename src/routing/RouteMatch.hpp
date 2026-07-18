#pragma once

#include "config/ConfigModel.hpp"
#include "http/HttpRequest.hpp"

struct RouteMatch {
    const LocationConfig* location;
    std::string resolvedPath;
};
