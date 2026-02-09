#ifndef MEGENGINEPROJECT_INPUT_SYSTEM_H
#define MEGENGINEPROJECT_INPUT_SYSTEM_H

#include <memory>

#include "input_context.h"
#include "input_manager.h"
#include "input_mapping.h"
#include "MEGEngine/common.h"
#include "MEGEngine/input/input_action.h"
#include "MEGEngine/input/player_action_bus.h"

namespace MEGEngine {
    class ENGINE_API InputSystem {
    public:
        InputAction& createAction(std::string name, InputAction::Type type);
        std::shared_ptr<InputContext> createContext();
        void bind(InputContext& ctx, InputAction& action, InputSource src, float scale = 1.0f);
        void pushContext(std::shared_ptr<InputContext> ctx);
        void subscribe(InputAction& action, PlayerActionBus::Callback cb);
        void update();
        InputManager& manager() { return _manager; }
        InputMappingSystem& mapping() {return _mapping; };
        void init();

    private:
        InputManager _manager;
        InputMappingSystem _mapping;
        PlayerActionBus _actionBus;

        std::vector<std::shared_ptr<InputAction>> _actions;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_INPUT_SYSTEM_H