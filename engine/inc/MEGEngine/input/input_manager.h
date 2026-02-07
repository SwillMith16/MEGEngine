#ifndef MEGENGINEPROJECT_INPUT_MANAGER_H
#define MEGENGINEPROJECT_INPUT_MANAGER_H

#include "MEGEngine/common.h"
#include "MEGEngine/input/raw_input_event_bus.h"
#include "MEGEngine/input/input_device.h"

namespace MEGEngine {
    class ENGINE_API InputManager {
    public:
        static void addDevice(std::unique_ptr<IInputDevice> device);
        static void update();

        template<typename Event>
        static void emit(const Event& e) {
            _bus.queueEvent(e);
        }

    private:
        static RawInputEventBus _bus;
        static std::vector<std::unique_ptr<IInputDevice>> _devices;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_INPUT_MANAGER_H