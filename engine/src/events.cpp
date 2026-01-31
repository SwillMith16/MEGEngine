#include <typeinfo>

#include "MEGEngine/events.h"
#include "MEGEngine/event_manager.h"

namespace MEGEngine {
    EventListener::EventListener(Entity& parent) : _parent(parent) {}

    Entity& EventListener::parent() {
        return _parent;
    }
} // EVENT LISTENER

namespace MEGEngine {
    Event::Event() : _id(typeid(this).name()) {}

    std::string Event::type() {
        return _id;
    }
} // EVENT