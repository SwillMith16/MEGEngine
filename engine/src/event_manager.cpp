#include "MEGEngine/event_manager.h"

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
} // MEGEngine