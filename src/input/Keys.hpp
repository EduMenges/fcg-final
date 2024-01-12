#pragma once

#include <array>
#include <optional>

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Action.hpp"

namespace input {
struct Key {
    int  code_;
    bool pressed_ = false;

    void TakeAction(Action action) {
        switch (action) {
            case Action::kRelease:
                Off();
                break;
            case Action::kPress:
                On();
                break;
            case Action::kRepeat:
                // Do nothing for now.
                break;
        }
    }

    void On() { pressed_ = true; }

    void Off() { pressed_ = false; }
};

/// If a key is pressed, it is assigned `true`.
struct Keys {
    void TakeAction(int key, Action action) {
        if (auto* result = std::ranges::find_if(keys_, [&](Key i) { return i.code_ == key; }); result != keys_.end()) {
            result->TakeAction(action);
        }
    }

    [[nodiscard]] std::optional<bool> IsOn(char code) const {
        if (const auto* result = std::ranges::find_if(keys_, [&](Key i) { return i.code_ == code; }); result != keys_.end()) {
            return result->pressed_;
        }
        return std::nullopt;
    }

    static constexpr size_t        kAmountOfKeys = 4;
    std::array<Key, kAmountOfKeys> keys_         = {{{GLFW_KEY_W}, {GLFW_KEY_A}, {GLFW_KEY_S}, {GLFW_KEY_D}}};
};
}
