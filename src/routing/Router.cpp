#include "Router.hpp"

Router::Router(const ConfigModel& config) {
    (void)config;
}

RouteMatch Router::resolve(const ServerConfig& server, const HttpRequest& request) const {
    (void)server;
    (void)request;
    RouteMatch m;
    m.location = 0;
    m.resolvedPath = "";
    return m;
}
