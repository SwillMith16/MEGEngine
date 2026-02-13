#include "MEGEngine/input/player_action_bus.h"

namespace MEGEngine {
    void PlayerActionBus::subscribe(InputAction *action, Callback cb) {
        _listeners[action].push_back(cb);
    }

    void PlayerActionBus::publish(const std::unordered_map<InputAction *, ActionState> &states) {
        for (auto& [action, state] : states) {
            if (_listeners.count(action)) {
                for (auto& cb : _listeners[action]) {
                    cb(state);
                }
            }
        }
    }
} // MEGEngine