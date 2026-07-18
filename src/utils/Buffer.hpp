#pragma once

#include <string>

class Buffer {
public:
    void append(const std::string& data);
    const std::string& str() const;
    void consume(size_t n);
    void clear();

private:
    std::string _data;
};
