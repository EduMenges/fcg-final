#pragma once

#include "input/Keys.hpp"
#include "input/Mouse.hpp"

class Input {
public:
    static Input &Instance() {
        static Input instance;
        return instance;
    }

    [[nodiscard]] bool IsOn(int code) const {
        return keys_.IsOn(code);
    }

    [[nodiscard]] auto GetDelta() const {
        return mouse_.GetDelta();
    }

    void UpdateMouse();

    input::Keys keys_;
    input::Mouse mouse_;

private:
    Input() = default;
};
