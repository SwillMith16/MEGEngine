#ifndef MEGENGINEPROJECT_TIMER_H
#define MEGENGINEPROJECT_TIMER_H

#include <chrono>

#include "MEGEngine/common.h"

namespace MEGEngine {
    class ENGINE_API Timer {
    public:
        static float deltaTime();
    private:
        friend class Application;
        static void setDeltaTime(auto& lastTime) {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> delta = now - lastTime;
            lastTime = now;
            _deltaTime = delta.count();
        }
        inline static float _deltaTime;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_TIMER_H