#ifndef MEGENGINEPROJECT_INPUT_ACTION_H
#define MEGENGINEPROJECT_INPUT_ACTION_H

#include <string>
#include <variant>

#include "MEGEngine/common.h"
#include "MEGEngine/math/vec2.h"

namespace MEGEngine {
    class ENGINE_API ActionValue {
    public:
        using variant = std::variant<bool, float, Vec2>;

        ActionValue() : _value(false) {}
        ActionValue(bool v) : _value(v) {}
        ActionValue(float v) : _value(v) {}
        ActionValue(Vec2 v) : _value(v) {}

        const bool* asBool() const { return std::get_if<bool>(&_value); }
        const float* asFloat() const { return std::get_if<float>(&_value); }
        const Vec2* asVec2() const { return std::get_if<Vec2>(&_value); }

        const variant& asVariant() const { return _value; }

    private:
        variant _value;
    };

    struct ENGINE_API ActionState {
        ActionValue value;

        bool started = false;
        bool ongoing = false;
        bool completed = false;
    };

    class ENGINE_API InputAction {
    public:
        enum class Type {
            BOOL,
            FLOAT,
            VEC2
        };

        InputAction(std::string name, Type type) : _name(std::move(name)), _type(type) {}

        std::string name() const { return _name; }

    private:
        std::string _name;
        Type _type;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_INPUT_ACTION_H