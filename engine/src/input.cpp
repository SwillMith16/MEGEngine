#include "GLFW/glfw3.h"

#include "MEGEngine/input.h"
#include "MEGEngine/events.h"
#include "MEGEngine/event_manager.h"
#include "MEGEngine/window.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    struct WindowImpl {
        GLFWwindow* impl;
    };

    void WASDLayout::KeyPress_W() {
        EventManager::triggerEvent<MoveForwardEvent>();
    }
    void WASDLayout::KeyPress_1() {
        InputManager::bindInputLayout<WASDLayout>();
    }
    void WASDLayout::KeyPress_2() {
        InputManager::bindInputLayout<ArrowLayout>();
    }

    void ArrowLayout::KeyPress_UpArrow() {
        EventManager::triggerEvent<MoveForwardEvent>();
    }
    void ArrowLayout::KeyPress_1() {
        InputManager::bindInputLayout<WASDLayout>();
    }
    void ArrowLayout::KeyPress_2() {
        InputManager::bindInputLayout<ArrowLayout>();
    }

    void InputManager::processInputs() {
        if (!_window) // pointer to window must be set
            return;

        auto* glfwWindow = static_cast<WindowImpl*>(static_cast<void*>(&_window->impl()));
        // Handles key inputs
        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_W) == GLFW_PRESS)
        {
            // Log(LogLevel::DBG, "W pressed");
            _inputLayouts[_activeInputLayout]->KeyPress_W();
        }

        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_UP) == GLFW_PRESS)
        {
            // Log(LogLevel::DBG, "Up Arrrow pressed");
            _inputLayouts[_activeInputLayout]->KeyPress_UpArrow();
        }

        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_1) == GLFW_PRESS)
        {
            // Log(LogLevel::DBG, "1 pressed");
            _inputLayouts[_activeInputLayout]->KeyPress_1();
        }

        if (glfwGetKey(glfwWindow->impl, GLFW_KEY_2) == GLFW_PRESS)
        {
            // Log(LogLevel::DBG, "2 pressed");
            _inputLayouts[_activeInputLayout]->KeyPress_2();
        }
    }
} // MEGEngine