#ifndef MEGENGINEPROJECT_INPUT_H
#define MEGENGINEPROJECT_INPUT_H

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "MEGEngine/common.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    class ENGINE_API InputLayout {
    public:
        InputLayout() = default;
        virtual ~InputLayout() = default;

        void unbindFromWindow();

        virtual void KeyPress_W() {}
        virtual void KeyPress_UpArrow() {}
        virtual void KeyPress_1() {}
        virtual void KeyPress_2() {}
    };


    class ENGINE_API WASDLayout : public InputLayout {
        void KeyPress_1() override;
        void KeyPress_2() override;
        void KeyPress_W() override;
    };
    class ENGINE_API ArrowLayout : public InputLayout {
        void KeyPress_1() override;
        void KeyPress_2() override;
        void KeyPress_UpArrow() override;
    };
} // INPUT LAYOUT




namespace MEGEngine {
    // Static class that keeps references to custom input layouts for access throughout the application
    class ENGINE_API InputManager {
    public:
        // Initialise the input manager with a pointer to the window object
        static void init(class Window* window) {
            if (!window) {
                Log(LogLevel::ERR, "MEGEngine::InputManager::init failed: window is null");
                return;
            }
            Log(LogLevel::DBG, "MEGEngine::InputManager::init");
            _window = window;
        }

        // Bind an InputLayout. Window pointer used in checking for inputs each frame.
        // Creates and stores an instance of the given InputLayout, and sets it as active.
        template<typename LayoutType>
        static void bindInputLayout() {
            static_assert(std::is_base_of_v<InputLayout, LayoutType>);
            auto layout = std::make_unique<LayoutType>();
            LayoutType& ref = *layout;
            _inputLayouts[typeid(LayoutType)] = std::move(layout);
            _activeInputLayout = typeid(LayoutType);
        }

        static void unbindInputLayout() { _activeInputLayout = typeid(InputLayout); }

        static void processInputs();

    private:
        inline static std::unordered_map<std::type_index, std::unique_ptr<InputLayout>> _inputLayouts;
        inline static std::type_index _activeInputLayout = typeid(InputLayout);
        inline static Window* _window = nullptr;
    };
} // INPUT MANAGER

#endif //MEGENGINEPROJECT_INPUT_H