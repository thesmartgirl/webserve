#pragma once

#include <map>
#include <string>
#include <vector>

struct LocationConfig {
    std::string pathPrefix;
    std::string root;
    std::vector<std::string> indexFiles;
    bool autoindex;
    std::vector<std::string> allowedMethods;
    std::string uploadDir;
};

struct ServerConfig {
    std::string listenHost;
    int listenPort;
    std::vector<std::string> serverNames;
    size_t clientMaxBodySize;
    std::map<int, std::string> errorPages;
    std::vector<LocationConfig> locations;
};

struct ConfigModel {
    std::vector<ServerConfig> servers;
};
