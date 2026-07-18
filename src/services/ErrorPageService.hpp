#pragma once

#include "http/HttpResponse.hpp"

class ErrorPageService {
public:
    HttpResponse makeError(int statusCode) const;
};
