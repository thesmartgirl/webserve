#include "TimeUtils.hpp"

std::time_t TimeUtils::now() {
    return std::time(0);
}
