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
        static constexpr std::array<KeyCode, GLFW_KEY_LAST> buildTable()
        {
            std::array<KeyCode, GLFW_KEY_LAST> table{};

            table.fill(KeyCode::UNKNOWN);
            table[GLFW_KEY_SPACE] = KeyCode::SPACE;
            table[GLFW_KEY_APOSTROPHE] = KeyCode::APOSTROPHE;
            table[GLFW_KEY_COMMA] = KeyCode::COMMA;
            table[GLFW_KEY_MINUS] = KeyCode::MINUS;
            table[GLFW_KEY_PERIOD] = KeyCode::PERIOD;
            table[GLFW_KEY_SLASH] = KeyCode::SLASH;
            table[GLFW_KEY_0] = KeyCode::NUM0;
            table[GLFW_KEY_1] = KeyCode::NUM1;
            table[GLFW_KEY_2] = KeyCode::NUM2;
            table[GLFW_KEY_3] = KeyCode::NUM3;
            table[GLFW_KEY_4] = KeyCode::NUM4;
            table[GLFW_KEY_5] = KeyCode::NUM5;
            table[GLFW_KEY_6] = KeyCode::NUM6;
            table[GLFW_KEY_7] = KeyCode::NUM7;
            table[GLFW_KEY_8] = KeyCode::NUM8;
            table[GLFW_KEY_9] = KeyCode::NUM9;
            table[GLFW_KEY_SEMICOLON] = KeyCode::SEMICOLON;
            table[GLFW_KEY_EQUAL] = KeyCode::EQUAL;
            table[GLFW_KEY_A] = KeyCode::A;
            table[GLFW_KEY_B] = KeyCode::B;
            table[GLFW_KEY_C] = KeyCode::C;
            table[GLFW_KEY_D] = KeyCode::D;
            table[GLFW_KEY_E] = KeyCode::E;
            table[GLFW_KEY_F] = KeyCode::F;
            table[GLFW_KEY_G] = KeyCode::G;
            table[GLFW_KEY_H] = KeyCode::H;
            table[GLFW_KEY_I] = KeyCode::I;
            table[GLFW_KEY_J] = KeyCode::J;
            table[GLFW_KEY_K] = KeyCode::K;
            table[GLFW_KEY_L] = KeyCode::L;
            table[GLFW_KEY_M] = KeyCode::M;
            table[GLFW_KEY_N] = KeyCode::N;
            table[GLFW_KEY_O] = KeyCode::O;
            table[GLFW_KEY_P] = KeyCode::P;
            table[GLFW_KEY_Q] = KeyCode::Q;
            table[GLFW_KEY_R] = KeyCode::R;
            table[GLFW_KEY_S] = KeyCode::S;
            table[GLFW_KEY_T] = KeyCode::T;
            table[GLFW_KEY_U] = KeyCode::U;
            table[GLFW_KEY_V] = KeyCode::V;
            table[GLFW_KEY_W] = KeyCode::W;
            table[GLFW_KEY_X] = KeyCode::X;
            table[GLFW_KEY_Y] = KeyCode::Y;
            table[GLFW_KEY_Z] = KeyCode::Z;
            table[GLFW_KEY_LEFT_BRACKET] = KeyCode::LEFT_BRACKET;
            table[GLFW_KEY_BACKSLASH] = KeyCode::BACKSLASH;
            table[GLFW_KEY_RIGHT_BRACKET] = KeyCode::RIGHT_BRACKET;
            table[GLFW_KEY_GRAVE_ACCENT] = KeyCode::GRAVE_ACCENT;
            table[GLFW_KEY_WORLD_1] = KeyCode::WORLD_1;
            table[GLFW_KEY_WORLD_2] = KeyCode::WORLD_2;
            table[GLFW_KEY_ESCAPE] = KeyCode::ESCAPE;
            table[GLFW_KEY_ENTER] = KeyCode::ENTER;
            table[GLFW_KEY_TAB] = KeyCode::TAB;
            table[GLFW_KEY_BACKSPACE] = KeyCode::BACKSPACE;
            table[GLFW_KEY_INSERT] = KeyCode::INSERT;
            table[GLFW_KEY_DELETE] = KeyCode::DELETE;
            table[GLFW_KEY_RIGHT] = KeyCode::RIGHT;
            table[GLFW_KEY_LEFT] = KeyCode::LEFT;
            table[GLFW_KEY_DOWN] = KeyCode::DOWN;
            table[GLFW_KEY_UP] = KeyCode::UP;
            table[GLFW_KEY_PAGE_UP] = KeyCode::PAGE_UP;
            table[GLFW_KEY_PAGE_DOWN] = KeyCode::PAGE_DOWN;
            table[GLFW_KEY_HOME] = KeyCode::HOME;
            table[GLFW_KEY_END] = KeyCode::END;
            table[GLFW_KEY_CAPS_LOCK] = KeyCode::CAPS_LOCK;
            table[GLFW_KEY_SCROLL_LOCK] = KeyCode::SCROLL_LOCK;
            table[GLFW_KEY_NUM_LOCK] = KeyCode::NUM_LOCK;
            table[GLFW_KEY_PRINT_SCREEN] = KeyCode::PRINT_SCREEN;
            table[GLFW_KEY_PAUSE] = KeyCode::PAUSE;
            table[GLFW_KEY_F1] = KeyCode::F1;
            table[GLFW_KEY_F2] = KeyCode::F2;
            table[GLFW_KEY_F3] = KeyCode::F3;
            table[GLFW_KEY_F4] = KeyCode::F4;
            table[GLFW_KEY_F5] = KeyCode::F5;
            table[GLFW_KEY_F6] = KeyCode::F6;
            table[GLFW_KEY_F7] = KeyCode::F7;
            table[GLFW_KEY_F8] = KeyCode::F8;
            table[GLFW_KEY_F9] = KeyCode::F9;
            table[GLFW_KEY_F10] = KeyCode::F10;
            table[GLFW_KEY_F11] = KeyCode::F11;
            table[GLFW_KEY_F12] = KeyCode::F12;
            table[GLFW_KEY_F13] = KeyCode::F13;
            table[GLFW_KEY_F14] = KeyCode::F14;
            table[GLFW_KEY_F15] = KeyCode::F15;
            table[GLFW_KEY_F16] = KeyCode::F16;
            table[GLFW_KEY_F17] = KeyCode::F17;
            table[GLFW_KEY_F18] = KeyCode::F18;

            return table;
        }

        static inline const std::array<KeyCode, GLFW_KEY_LAST> _table = buildTable();
    };
}

#endif //MEGENGINEPROJECT_GLFW_KEY_TRANSLATOR_H