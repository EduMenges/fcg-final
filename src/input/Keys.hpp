#pragma once

#include <array>
#include <optional>
#include <ranges>

#include "OpenGL.h"

#include "Action.hpp"

namespace input {
struct Key {
    int  code;
    bool pressed = false;

    void TakeAction(Action action) {
        switch (action) {
            case Action::kRelease:
                Off();
                break;
            case Action::kPress:
                On();
                break;
            case Action::kRepeat:
                // Do nothing
                break;
        }
    }

    constexpr void On() { pressed = true; }

    constexpr void Off() { pressed = false; }
};

struct Keys {
    void TakeAction(int key, Action action) {
        if (auto result = std::ranges::find_if(keys_, [&](Key i) { return i.code == key; }); result != keys_.end()) {
            result->TakeAction(action);
        }
    }

    /// This function will panic if @p code is not on the @keys list.
    [[nodiscard]] bool IsOn(int code) const {
        const auto result = std::ranges::find_if(keys_, [&](Key i) { return i.code == code; });
        return result->pressed;
    }

    static constexpr size_t        kAmountOfKeys = 8;
    std::array<Key, kAmountOfKeys> keys_         = {
        {{GLFW_KEY_W}, {GLFW_KEY_A}, {GLFW_KEY_S}, {GLFW_KEY_D}, {GLFW_KEY_ESCAPE}, {GLFW_KEY_ENTER}, {GLFW_KEY_E}, {GLFW_KEY_Q}}};
};
}
