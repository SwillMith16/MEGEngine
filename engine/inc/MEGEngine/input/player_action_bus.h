#ifndef MEGENGINEPROJECT_PLAYER_ACTION_BUS_H
#define MEGENGINEPROJECT_PLAYER_ACTION_BUS_H

#include <functional>

#include "MEGEngine/common.h"
#include "MEGEngine/input/input_action.h"

namespace MEGEngine {
    class ENGINE_API PlayerActionBus {
    public:
        using Callback = std::function<void(const ActionState&)>;

        void subscribe(InputAction* action, Callback cb);
        void publish(const std::unordered_map<InputAction*, ActionState>& states);

    private:
        std::unordered_map<InputAction*, std::vector<Callback>> _listeners;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_PLAYER_ACTION_BUS_H