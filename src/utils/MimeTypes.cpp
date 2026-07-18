#include "MimeTypes.hpp"

std::string MimeTypes::fromPath(const std::string& path) {
    (void)path;
    return "application/octet-stream";
}
