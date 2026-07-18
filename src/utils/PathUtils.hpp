#pragma once

#include <string>

class PathUtils {
public:
    static std::string normalize(const std::string& path);
    static bool isSafePath(const std::string& root, const std::string& candidate);
};
