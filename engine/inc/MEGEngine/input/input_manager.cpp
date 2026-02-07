#include "input_manager.h"

namespace MEGEngine {
    RawInputEventBus InputManager::_bus;
    std::vector<std::unique_ptr<IInputDevice>> InputManager::_devices;

    void InputManager::addDevice(std::unique_ptr<IInputDevice> device) {
        Log(LogLevel::DBG, "Device added to input manager");
        device->initialise(_bus);
        _devices.push_back(std::move(device));
    }

    void InputManager::update() {
        for (auto& device : _devices)
            device->poll();

        _bus.dispatch();
    }
} // MEGEngine