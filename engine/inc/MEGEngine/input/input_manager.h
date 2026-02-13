#ifndef MEGENGINEPROJECT_INPUT_MANAGER_H
#define MEGENGINEPROJECT_INPUT_MANAGER_H

#include "MEGEngine/common.h"
#include "MEGEngine/input/raw_input_event_bus.h"
#include "MEGEngine/input/input_device.h"

namespace MEGEngine {
    class ENGINE_API InputManager {
    public:
        void addDevice(std::unique_ptr<Base_InputDevice> device);
        void update();

        template<typename Event>
        void emit(const Event& e) {
            _bus.queueEvent(e);
        }

        RawInputEventBus& bus() { return _bus; }

    private:
        RawInputEventBus _bus;
        std::vector<std::unique_ptr<Base_InputDevice>> _devices;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_INPUT_MANAGER_H