#ifndef MEGENGINEPROJECT_EVENTS_H
#define MEGENGINEPROJECT_EVENTS_H

#include <typeindex>
#include <unordered_map>
#include <vector>

#include "MEGEngine/common.h"

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
    class ENGINE_API EventManager {
    public:
        static void processEvents();

        template <typename EventType>
        static void addListener(EventListener& listener) {
            static_assert(std::is_base_of_v<Event, EventType>);
            _listeners[typeid(EventType)].push_back(&listener);
        }

        template<typename EventType>
        static void triggerEvent()
        {
            _eventQueue.emplace_back(typeid(EventType));
        }

    private:
        inline static std::vector<std::type_index> _eventQueue;
        inline static std::unordered_map<std::type_index, std::vector<EventListener*>> _listeners;
    };
} // EVENT MANAGER

#endif //MEGENGINEPROJECT_EVENTS_H