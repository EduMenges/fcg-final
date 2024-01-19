#pragma once

#include "input/Keys.hpp"
#include "input/Mouse.hpp"

class Input {
public:
    static Input &Instance() {
        static Input instance;
        return instance;
    }

    bool IsOn(int code) {
        return keys_.IsOn(code);
    }

    [[nodiscard]] constexpr auto GetDelta() const {
        return mouse_.GetDelta();
    }

    input::Keys keys_;
    input::Mouse mouse_;

private:
    Input() = default;
};
