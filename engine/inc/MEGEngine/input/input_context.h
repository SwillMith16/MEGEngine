#ifndef MEGENGINEPROJECT_INPUT_CONTEXT_H
#define MEGENGINEPROJECT_INPUT_CONTEXT_H


#include "MEGEngine/common.h"
#include "MEGEngine/input/input_events.h"
#include "MEGEngine/input/input_action.h"

namespace MEGEngine {
    class InputContext;
    struct InputSource;
    struct InputBinding;

    struct ENGINE_API InputSource {
        enum class Type {
            KEY,
            MOUSE_DELTA
        };

        Type type;

        KeyCode key;
    };

    struct ENGINE_API InputBinding {
        InputAction* action; // can be null if no action is bound
        InputSource source; // cannot be null, must have a source that triggers it
        float scale = 1.0f;
    };

    class ENGINE_API InputContext {
    public:
        void addBinding(const InputBinding& binding) { _bindings.push_back(binding); }
        const std::vector<InputBinding>& bindings() const { return _bindings; }

    private:
        std::vector<InputBinding> _bindings;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_INPUT_CONTEXT_H