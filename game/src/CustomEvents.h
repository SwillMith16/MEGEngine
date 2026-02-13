#ifndef CUSTOMEVENTS_H
#define CUSTOMEVENTS_H

#include "MEGEngine/events.h"
#include "MEGEngine/utils/log.h"

class TestEvent : public MEGEngine::Event {};
class TestEventListener : public MEGEngine::EventListener {
public:
    TestEventListener(MEGEngine::Entity& parent) : EventListener(parent) {}

    void onEvent() override {
        MEGEngine::Log(LogLevel::DBG, "Test Event Listener received trigger");
    }
};

#endif //CUSTOMEVENTS_H