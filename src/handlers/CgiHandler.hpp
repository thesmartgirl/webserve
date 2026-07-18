#pragma once

#include "IHandler.hpp"

class CgiHandler : public IHandler {
public:
    HttpResponse handle(const HttpRequest& req, const RouteContext& ctx);
};
