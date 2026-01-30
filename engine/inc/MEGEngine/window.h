#ifndef MEGENGINEPROJECT_WINDOW_H
#define MEGENGINEPROJECT_WINDOW_H

#include <string>

#include "MEGEngine/common.h"

namespace MEGEngine {
    class ENGINE_API Window {
        struct Impl;
    public:
        Window();
        ~Window();

        // Prevents copying of the instance
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;

        // Create and display a blank window
        void create(const std::string& title = "MEGEngine Window",
                    int width = 1280,
                    int height = 720);

        // Check for events that need to be processed. Key or mouse clicks etc.
        void pollEvents();
        // Check if an action has happened that should cause the application to close
        bool shouldClose() const;
        // Display what has been rendered on the window
        void display();

        Impl& impl();

    private:
        // Private wrapper for GLFWwindow to keep it hidden from public headers
        Impl* _impl;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_WINDOW_H