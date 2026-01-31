#include "MEGEngine/event_manager.h"

namespace MEGEngine {
    void EventManager::processEvents() {
        for (const auto& eventID: _eventQueue) {
            auto foundEvent = _listeners.find(eventID);
            if (foundEvent == _listeners.end())
                continue;

            for (EventListener* listener: foundEvent->second) {
                listener->onEvent();
            }
        }
        _eventQueue.clear();
    }
} // MEGEngine