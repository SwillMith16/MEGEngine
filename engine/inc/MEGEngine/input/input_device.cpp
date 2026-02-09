#include "GLFW/glfw3.h"

#include "MEGEngine/input/input_device.h"
#include "MEGEngine/input/raw_input_event_bus.h"
#include "MEGEngine/window.h"
#include "MEGEngine/input/glfw_key_translator.h"

namespace MEGEngine {
    struct WindowImpl {
        GLFWwindow* handle = nullptr;
    };

    void KeyboardDevice::poll() {
        WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));
        for (int key = GLFW_KEY_SPACE; key <= GLFW_KEY_LAST; ++key) {
            bool isDown = glfwGetKey(glfwWindow->handle, key) == GLFW_PRESS;

            if (isDown && !_previous[key]) {
                _bus->queueEvent(KeyPressedEvent{.key = GLFWKeyTranslator::translate(key)});
            }
            else if (!isDown && _previous[key]) {
                _bus->queueEvent(KeyReleasedEvent{.key = GLFWKeyTranslator::translate(key)});
            }

            _previous[key] = isDown;
        }
    }

    void MouseDevice::initialise(RawInputEventBus& bus) {
        WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));
        _bus = &bus;
        glfwGetCursorPos(glfwWindow->handle, &_lastX, &_lastY);
    }
    void MouseDevice::poll() {
        WindowImpl* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));

        double x, y;
        glfwGetCursorPos(glfwWindow->handle, &x, &y);

        float dx = float(x - _lastX);
        float dy = float(y - _lastY);

        if (dx != 0 || dy != 0) {
            _bus->queueEvent(MouseMovedEvent{.x = float(x), .y = float(y), .dx = dx, .dy = dy});
        }

        _lastX = x;
        _lastY = y;
    }








}
