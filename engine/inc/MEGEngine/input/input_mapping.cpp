#include "MEGEngine/input/input_mapping.h"

namespace MEGEngine {
    void InputMappingSystem::attachBus(RawInputEventBus &bus) {
        // subscribe 'onKeyPressed' function to listen for key press events
        bus.subscribe<KeyPressedEvent>([this](auto& e) { onKeyPressed(e); });

        bus.subscribe<KeyReleasedEvent>([this](auto& e) { onKeyReleased(e); });

        bus.subscribe<MouseMovedEvent>([this](auto& e) { onMouseMoved(e); });
    }

    void InputMappingSystem::pushContext(std::shared_ptr<InputContext> context) { _contexts.push(context); }

    void InputMappingSystem::popContext() {
        if (!_contexts.empty())
            _contexts.pop();
    }

    void InputMappingSystem::beginFrame() {
        for (auto& [a, s] : _states) {
            s.started = false;
            s.completed = false;
        }
    }

    const std::unordered_map<InputAction*, ActionState>& InputMappingSystem::states() const {
        return _states;
    }

    void InputMappingSystem::apply(InputAction* action, ActionValue v) {
        auto& state = _states[action];

        bool wasActive = state.ongoing;

        state.value = v;
        state.ongoing = true;

        if (!wasActive)
            state.started = true;
    }

    void InputMappingSystem::release(InputAction* action) {
        auto& state = _states[action];

        if (state.ongoing)
        {
            state.ongoing = false;
            state.completed = true;
            state.value = ActionValue(false);
        }
    }

    void InputMappingSystem::onKeyPressed(const KeyPressedEvent& e) {
        if (_contexts.empty()) return;

        for (auto& b : _contexts.top()->bindings()) {
            if (b.source.type == InputSource::Type::KEY && b.source.key == e.key) {
                apply(b.action, ActionValue(b.scale));
            }
        }
    }

    void InputMappingSystem::onKeyReleased(const KeyReleasedEvent& e) {
        if (_contexts.empty()) return;

        for (auto& b : _contexts.top()->bindings()) {
            if (b.source.type == InputSource::Type::KEY && b.source.key == e.key) {
                release(b.action);
            }
        }
    }

    void InputMappingSystem::onMouseMoved(const MouseMovedEvent& e) {
        if (_contexts.empty()) return;

        for (auto& b : _contexts.top()->bindings()) {
            if (b.source.type == InputSource::Type::MOUSE_DELTA) {
                apply(b.action, ActionValue(Vec2{e.dx, e.dy}));
            }
        }
    }
} // MEGEngine