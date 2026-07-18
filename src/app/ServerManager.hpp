#pragma once

class ServerManager {
public:
    ServerManager();
    void initialize(const char* configPath);
    void run();
};
