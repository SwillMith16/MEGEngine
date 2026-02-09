#include "MEGEngine/input/input_system.h"

#include "MEGEngine/engine.h"

namespace MEGEngine {
    void InputSystem::init() {
        Engine::instance().setInputSystem(this);
        _mapping.attachBus(_manager.bus());
    }
    InputAction& InputSystem::createAction(std::string name, InputAction::Type type) {
        _actions.push_back(std::make_unique<InputAction>(name, type));
        return *_actions.back();
    }

    std::shared_ptr<InputContext> InputSystem::createContext() {
        return std::make_shared<InputContext>();
    }

    void InputSystem::bind(InputContext& ctx, InputAction& action, InputSource src, float scale) {
        ctx.addBinding(InputBinding{&action, src, scale});
    }

    void InputSystem::pushContext(std::shared_ptr<InputContext> ctx) {
        _mapping.pushContext(ctx);
    }

    void InputSystem::subscribe(InputAction &action, PlayerActionBus::Callback cb) {
        _actionBus.subscribe(&action, std::move(cb));
    }

    void InputSystem::update() {
        _mapping.beginFrame();
        _manager.update();
        _actionBus.publish(_mapping.states());
    }
} // MEGEngine