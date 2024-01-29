#pragma once

#include <array>
#include <optional>
#include <ranges>

#include "OpenGL.h"

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
                // Do nothing
                break;
        }
    }

    constexpr void On() { pressed_ = true; }

    constexpr void Off() { pressed_ = false; }
};

struct Keys {
    void TakeAction(int key, Action action) {
        if (auto result = std::ranges::find_if(keys_, [&](Key i) { return i.code_ == key; }); result != keys_.end()) {
            result->TakeAction(action);
        }
    }

    [[nodiscard]] bool IsOn(int code) const {
        const auto result = std::ranges::find_if(keys_, [&](Key i) { return i.code_ == code; });
        return result->pressed_;
    }

    static constexpr size_t        kAmountOfKeys = 5;
    std::array<Key, kAmountOfKeys> keys_         = {
        {{GLFW_KEY_W}, {GLFW_KEY_A}, {GLFW_KEY_S}, {GLFW_KEY_D}, {GLFW_KEY_ESCAPE}}};
};
}
