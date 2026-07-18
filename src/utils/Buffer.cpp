#include "Buffer.hpp"

void Buffer::append(const std::string& data) { _data += data; }

const std::string& Buffer::str() const { return _data; }

void Buffer::consume(size_t n) {
    if (n >= _data.size()) {
        _data.clear();
        return;
    }
    _data.erase(0, n);
}

void Buffer::clear() { _data.clear(); }
