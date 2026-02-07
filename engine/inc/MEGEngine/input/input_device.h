#ifndef MEGENGINEPROJECT_INPUT_DEVICE_H
#define MEGENGINEPROJECT_INPUT_DEVICE_H

#include <array>

// TODO: remove temp debugging includes
#include <typeinfo>
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    class IInputDevice {
    public:
        virtual ~IInputDevice() = default;

        virtual void initialise(class RawInputEventBus& bus) {
            Log(LogLevel::DBG, "Initialising device %s", typeid(*this).name());
            _bus = &bus;
        }

        virtual void poll() = 0;

    protected:
        RawInputEventBus* _bus = nullptr;
    };


    class KeyboardDevice : public IInputDevice {
    public:
        KeyboardDevice(class Window* window) : _window(window) {}
        void poll() override;

    private:
        Window* _window;

        // 349 is GLFW_KEY_LAST+1
        std::array<bool, 349> _previous{};
    };

    class MouseDevice : public IInputDevice {
    public:
        MouseDevice(class Window* window) : _window(window) {}
        void initialise(class RawInputEventBus& bus) override;
        void poll() override;

    private:
        Window* _window;
        double _lastX = 0;
        double _lastY = 0;
    };

    // TODO: add gamepad device for controller support

}

#endif //MEGENGINEPROJECT_INPUT_DEVICE_H