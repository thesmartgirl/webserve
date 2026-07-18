#include "StaticFileService.hpp"

HttpResponse StaticFileService::serveFile(const std::string& path, const RouteContext& ctx) const {
    (void)path;
    (void)ctx;
    return HttpResponse();
}
