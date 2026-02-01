#ifndef MEGENGINEPROJECT_EVENTS_H
#define MEGENGINEPROJECT_EVENTS_H

#include <string>
#include <typeindex>

#include "MEGEngine/common.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    class ENGINE_API Event {
    public:
        Event() = default;
    };
} // EVENT


namespace MEGEngine {
    class ENGINE_API EventListener {
    public:
        EventListener(class Entity& parent);
        virtual ~EventListener() = default;

        virtual void onEvent() {};

        Entity& parent();

    protected:
        Entity& _parent;
    };
} // EVENT LISTENER

namespace MEGEngine {
    class MoveForwardEvent : public Event {};
    class MoveForwardEventListener : public EventListener {
    public:
        MoveForwardEventListener(Entity& parent) : EventListener(parent) {}
        void onEvent() override {
            Log(LogLevel::DBG, "Move Forward!");
        }
    };
}

#endif //MEGENGINEPROJECT_EVENTS_H