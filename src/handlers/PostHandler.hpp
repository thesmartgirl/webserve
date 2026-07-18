#pragma once

#include "IHandler.hpp"

class PostHandler : public IHandler {
public:
    HttpResponse handle(const HttpRequest& req, const RouteContext& ctx);
};
