#include "ConfigParser.hpp"
#include "ConfigModel.hpp"

ConfigParser::ConfigParser() {}

ConfigModel ConfigParser::parseFile(const char* path) const {
    (void)path;
    return ConfigModel();
}
