#ifndef MEGENGINEPROJECT_INPUT_EVENTS_H
#define MEGENGINEPROJECT_INPUT_EVENTS_H
#include <functional>
#include <vector>

namespace MEGEngine {
    enum class KeyCode {
        UNKNOWN = 0,
        SPACE,
        APOSTROPHE,
        COMMA,
        MINUS,
        PERIOD,
        SLASH,
        NUM0,
        NUM1,
        NUM2,
        NUM3,
        NUM4,
        NUM5,
        NUM6,
        NUM7,
        NUM8,
        NUM9,
        SEMICOLON,
        EQUAL,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        LEFT_BRACKET,
        BACKSLASH,
        RIGHT_BRACKET,
        GRAVE_ACCENT,
        WORLD_1,
        WORLD_2,
        ESCAPE,
        ENTER,
        TAB,
        BACKSPACE,
        INSERT,
        DELETE,
        RIGHT,
        LEFT,
        DOWN,
        UP,
        PAGE_UP,
        PAGE_DOWN,
        HOME,
        END,
        CAPS_LOCK,
        SCROLL_LOCK,
        NUM_LOCK,
        PRINT_SCREEN,
        PAUSE,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        END_COUNT
    };

    struct KeyPressedEvent {
        KeyCode key;
    };

    struct KeyReleasedEvent {
        KeyCode key;
    };

    struct MouseMovedEvent {
        float x;
        float y;
        float dx;
        float dy;
    };

    class IQueuedEvent {
    public:
        virtual ~IQueuedEvent() = default;
        virtual void dispatch() = 0;
    };

    template<typename Event>
    class QueuedEvent : public IQueuedEvent {
    public:
        // Create a queued event object with the event it should be, and a list of it's listeners
        QueuedEvent(const Event& e, std::vector<std::function<void(const Event&)>>& listeners)
            : _event(e), _listeners(listeners) {}

        // Execute the event
        void dispatch() override {
            for (auto& l : _listeners)
                l(_event);
        }

    private:
        Event _event;
        std::vector<std::function<void(const Event&)>>& _listeners;
    };
}

#endif //MEGENGINEPROJECT_INPUT_EVENTS_H