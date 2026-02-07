#ifndef MEGENGINEPROJECT_GLFW_KEY_TRANSLATOR_H
#define MEGENGINEPROJECT_GLFW_KEY_TRANSLATOR_H

// DO NOT INCLUDE IN ANY PUBLIC HEADERS!!!!! cpp files only

#include "GLFW/glfw3.h"

#include "MEGEngine/input/input_events.h"

namespace MEGEngine {
    class GLFWKeyTranslator
    {
    public:

        static KeyCode translate(int glfwKey) {
            if (glfwKey < 0 || glfwKey > GLFW_KEY_LAST)
                return KeyCode::UNKNOWN;

            return _table[glfwKey];
        }

    private:

        // TODO: fill this out with the rest of the keys
        static constexpr std::array<KeyCode, GLFW_KEY_LAST + 1> buildTable()
        {
            std::array<KeyCode, GLFW_KEY_LAST + 1> table{};

            table.fill(KeyCode::UNKNOWN);

            table[GLFW_KEY_W] = KeyCode::W;
            table[GLFW_KEY_A] = KeyCode::A;
            table[GLFW_KEY_S] = KeyCode::S;
            table[GLFW_KEY_D] = KeyCode::D;

            table[GLFW_KEY_SPACE]  = KeyCode::SPACE;
            table[GLFW_KEY_ESCAPE] = KeyCode::ESCAPE;

            return table;
        }

        static inline const std::array<KeyCode, 349> _table = buildTable();
    };
}

#endif //MEGENGINEPROJECT_GLFW_KEY_TRANSLATOR_H