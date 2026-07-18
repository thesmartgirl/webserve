#pragma once

#include "http/HttpRequest.hpp"
#include "http/HttpResponse.hpp"
#include "routing/RouteContext.hpp"

class IHandler {
public:
    virtual ~IHandler() {}
    virtual HttpResponse handle(const HttpRequest& req, const RouteContext& ctx) = 0;
};
