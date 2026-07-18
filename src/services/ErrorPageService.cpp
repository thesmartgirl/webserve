#include "ErrorPageService.hpp"

HttpResponse ErrorPageService::makeError(int statusCode) const {
    HttpResponse resp;
    resp.statusCode = statusCode;
    return resp;
}
