#pragma once

#include "IHandler.hpp"

class DeleteHandler : public IHandler {
public:
    HttpResponse handle(const HttpRequest& req, const RouteContext& ctx);
};
