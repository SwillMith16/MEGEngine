#include "raw_input_event_bus.h"

namespace MEGEngine {
    std::vector<std::unique_ptr<IQueuedEvent>> RawInputEventBus::_eventQueue;

    void RawInputEventBus::dispatch() {
        Log(LogLevel::DBG, "Dispatching events");
        for (auto& event : _eventQueue)
            event->dispatch();

        _eventQueue.clear();
    }

} // MEGEngine