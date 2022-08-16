#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include <framework_build.hpp>
#include <generic/signal_source.hpp>
#include <generic/vector2.hpp>

#include <unordered_map>

#include <stdio.h>

using namespace ai_framework;

namespace ai_framework::input {
    enum ButtonState {
        NONE = 0,
        MOUSE_LEFT = 1 << 1,
        MOUSE_MIDDLE = 1 << 2,
        MOUSE_RIGHT = 1 << 3
    };

    enum KeyType {
        UNKNOWN = -1,
        KEY_0 = 0x30,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_A = 0x41,
        KEY_B,
        KEY_C,
        KEY_D,
        KEY_E,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_I,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_M,
        KEY_N,
        KEY_O,
        KEY_P,
        KEY_Q,
        KEY_R,
        KEY_S,
        KEY_T,
        KEY_U,
        KEY_V,
        KEY_W,
        KEY_X,
        KEY_Y,
        KEY_Z,
        KEY_OS_KEY,
        KEY_NUMPAD_0 = 0x60,
        KEY_NUMPAD_1,
        KEY_NUMPAD_2,
        KEY_NUMPAD_3,
        KEY_NUMPAD_4,
        KEY_NUMPAD_5,
        KEY_NUMPAD_6,
        KEY_NUMPAD_7,
        KEY_NUMPAD_8,
        KEY_NUMPAD_9,
        KEY_MULTIPLY,
        KEY_ADD,
        KEY_SEPARATOR,
        KEY_SUBTRACT,
        KEY_DECIMAL,
        KEY_DIVIDE,
        KEY_F1 = 0x70,
        KEY_F2,
        KEY_F3,
        KEY_F4,
        KEY_F5,
        KEY_F6,
        KEY_F7,
        KEY_F8,
        KEY_F9,
        KEY_F10,
        KEY_F11,
        KEY_F12,
        KEY_F13,
        KEY_F14,
        KEY_F15,
        KEY_F16,
        KEY_F17,
        KEY_F18,
        KEY_F19,
        KEY_F20,
        KEY_F21,
        KEY_F22,
        KEY_F23,
        KEY_F24
    };

    struct MouseStateEventParam {
        ButtonState old_buttons;
        ButtonState buttons;
        IntVector2 position;
    };

    struct MousePositionEventParam {
        IntVector2 position;
        ButtonState buttons;
    };

    struct KeyUpdateEventParam {
        KeyType key;
        bool pressed;
    };

    struct AI_API InputManager : SignalSource {
        void update_position(const IntVector2 &new_position) {
            position = new_position;

            MousePositionEventParam p{position, (ButtonState) button_state};
            emit("mouse_position_update", &p);
        };

        void update_button_state(ButtonState new_state, bool value) {
            auto old_state = button_state;

            if (value)
                button_state |= (int) new_state;
            else
                button_state &= ~new_state;

            MouseStateEventParam p{(ButtonState) old_state, (ButtonState) button_state, position};
            emit("mouse_state_update", &p);
        }

        bool has_button(ButtonState button) {
            return (button_state & (int) button) > 0;
        }

        IntVector2 get_position() const {
            return position;
        }

        FloatVector2 get_position_float() const {
            return {(float) position.x, (float) position.y};
        }

        void update_key_state(KeyType t, bool x) {
            key_state[t] = x;

            KeyUpdateEventParam p{t, x};
            emit("key_update", &p);
        }

        bool get_key_state(KeyType t) {
            return key_state.contains(t) ? key_state[t] : false;
        }

      private:
        IntVector2 position{0, 0};
        int button_state = 0;

        std::unordered_map<KeyType, bool> key_state;
    };
} // namespace ai_framework::input

#endif