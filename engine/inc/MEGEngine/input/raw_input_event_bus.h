#ifndef MEGENGINEPROJECT_RAW_INPUT_EVENT_BUS_H
#define MEGENGINEPROJECT_RAW_INPUT_EVENT_BUS_H

#include "MEGEngine/input/input_shared_types.h"
#include "MEGEngine/input/input_events.h"

#include "MEGEngine/utils/log.h"

namespace MEGEngine {
    class RawInputEventBus {
    public:
        // listener is a pointer to a function that takes an event in its template
        template<typename Event>
        using Listener = std::function<void(const Event&)>;

        // add listener with the event type that will trigger it
        template<typename Event>
        static void subscribe(Listener<Event> listener) {
            Log(LogLevel::DBG, "Subscribe listener of event type %s to RawInputEventBus", typeid(Event).name());
            listeners<Event>().push_back(std::move(listener));
        }

        // Queue an event, with a list of its listeners attached
        template<typename Event>
        static void queueEvent(const Event& e) {
            Log(LogLevel::DBG, "Queue event of type %s to RawInputEventBus", typeid(Event).name());
            auto& vec = listeners<Event>();
            _eventQueue.push_back(std::make_unique<QueuedEvent<Event>>(e, vec));
        }

        void dispatch();

    private:
        static std::vector<std::unique_ptr<Base_QueuedEvent>> _eventQueue;

        template<typename Event>
        static std::vector<Listener<Event>>& listeners() {
            static std::vector<Listener<Event>> listeners;
            return listeners;
        }
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_RAW_INPUT_EVENT_BUS_H