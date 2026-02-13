#include "MEGEngine/events.h"
#include "MEGEngine/timer.h"

namespace MEGEngine {
    EventListener::EventListener(Entity& parent) : _parent(parent) {}

    Entity& EventListener::parent() {
        return _parent;
    }
} // EVENT LISTENER

namespace MEGEngine {
    void EventManager::processEvents() {
        for (const auto& eventType: _eventQueue) {
            auto foundEvent = _listeners[eventType];
            for (EventListener* listener: foundEvent) {
                listener->onEvent();
            }
        }
        _eventQueue.clear();
    }
} // EVENT MANAGER