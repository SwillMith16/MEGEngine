#ifndef MEGENGINEPROJECT_EVENT_MANAGER_H
#define MEGENGINEPROJECT_EVENT_MANAGER_H

#include <unordered_map>
#include <vector>

#include "MEGEngine/events.h"
#include "MEGEngine/common.h"

namespace MEGEngine {
    class ENGINE_API EventManager {
    public:
        static void processEvents();

        template <typename EventType>
        static void addListener(EventListener& listener) {
            static_assert(std::is_base_of_v<Event, EventType>);
            _listeners[getEventTypeID<EventType>()].push_back(&listener);
        }

        template<typename EventType>
        static void triggerEvent()
        {
            auto& listeners = _listeners[getEventTypeID<EventType>()];
            for (EventListener* listener : listeners)
            {
                listener->onEvent();
            }
        }

    private:
        inline static std::vector<EventTypeID> _eventQueue;
        inline static std::unordered_map<EventTypeID, std::vector<EventListener*>> _listeners;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_EVENT_MANAGER_H