#ifndef MEGENGINEPROJECT_LOG_H
#define MEGENGINEPROJECT_LOG_H

#include <string>

#include "common.h"

enum class ENGINE_API LogLevel {
    DBG,
    INF,
    WRN,
    ERR
};

namespace MEGEngine {
    void ENGINE_API Log(LogLevel level, const std::string& format, ...);
}

#endif //MEGENGINEPROJECT_LOG_H