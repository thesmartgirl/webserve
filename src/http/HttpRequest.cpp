#include "HttpRequest.hpp"

HttpRequest::HttpRequest() : method(HttpMethod::UNKNOWN), target(), version("HTTP/1.1"), headers(), body() {}
