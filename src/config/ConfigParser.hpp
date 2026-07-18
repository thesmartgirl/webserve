#pragma once

class ConfigModel;

class ConfigParser {
public:
    ConfigParser();
    ConfigModel parseFile(const char* path) const;
};
