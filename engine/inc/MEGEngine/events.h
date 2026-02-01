#ifndef MEGENGINEPROJECT_EVENTS_H
#define MEGENGINEPROJECT_EVENTS_H

#include <string>

#include "MEGEngine/common.h"
#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    class ENGINE_API Event {
    public:
        Event();

        std::string type();
    protected:
        std::string _id;
    };

    using EventTypeID = std::size_t;
    inline EventTypeID generateEventTypeID()
    {
        static EventTypeID last = 0;
        return last++;
    }

    template<typename T>
    EventTypeID getEventTypeID()
    {
        static EventTypeID id = generateEventTypeID();
        return id;
    }
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

class MoveForwardEvent : public MEGEngine::Event {};
class MoveForwardEventListener : public MEGEngine::EventListener {
public:
    MoveForwardEventListener(MEGEngine::Entity& parent) : EventListener(parent) {}
    void onEvent() override {
        MEGEngine::Log(LogLevel::DBG, "Move Forward!");
    }
};

#endif //MEGENGINEPROJECT_EVENTS_H