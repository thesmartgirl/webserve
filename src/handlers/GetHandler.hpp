#pragma once

#include "IHandler.hpp"

class GetHandler : public IHandler {
public:
    HttpResponse handle(const HttpRequest& req, const RouteContext& ctx);
};
