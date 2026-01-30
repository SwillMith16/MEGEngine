#include <cstdarg>
#include <iostream>
#include <chrono>

#include "MEGEngine/utils/log.h"

#ifdef __linux // _vscprintf is a windows function, not available on linux so defined here
int _vscprintf (const char * format, va_list pargs) {
    int retval;
    va_list argcopy;
    va_copy(argcopy, pargs);
    retval = vsnprintf(NULL, 0, format, argcopy);
    va_end(argcopy);
    return retval;
}
#endif

namespace MEGEngine {
    void Log(LogLevel level, const std::string& format, ...) {
        va_list args;
        int len;
        char* buffer;

        va_start(args, format);
        len = _vscprintf(format.c_str(), args) + 1;
        buffer = (char*) malloc(len * sizeof(char));
        vsprintf(buffer, format.c_str(), args);
        std::string msg = buffer;

        free(buffer);

        std::string levelStr;
        switch (level) {
            case LogLevel::DBG:
                levelStr = "DBG";
#ifndef DEBUG // only log this in debug builds
                return;
#endif
                break;
            case LogLevel::INF:
                levelStr = "INF";
#ifndef DEBUG // only log this in debug builds
                return;
#endif
                break;
            case LogLevel::WRN:
                levelStr = "WRN";
                break;
            case LogLevel::ERR:
                levelStr = "\033[31mERR\033[0m"; // colour codes for when displayed in terminal
                break;
        }
        //TODO: display logs to the game screen
        auto time = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now());
        auto formattedTime = std::format("{:%T}", time);
        std::cout << formattedTime << " [" << levelStr << "]: " << msg << std::endl;
    }
}