#pragma once

#include <string>
#include "routing/RouteContext.hpp"
#include "http/HttpResponse.hpp"

class StaticFileService {
public:
    HttpResponse serveFile(const std::string& path, const RouteContext& ctx) const;
};
