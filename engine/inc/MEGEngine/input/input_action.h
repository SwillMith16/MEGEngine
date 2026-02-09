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

        bool asBool() const { return std::get<bool>(_value); }
        float asFloat() const { return std::get<float>(_value); }
        Vec2 asVec2() const { return std::get<Vec2>(_value); }

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

    private:
        std::string _name;
        Type _type;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_INPUT_ACTION_H