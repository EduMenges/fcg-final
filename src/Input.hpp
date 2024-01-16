#pragma once

#include "input/Keys.hpp"
#include "input/Mouse.hpp"

class Input {
public:
    static Input &Instance() {
        static Input instance;
        return instance;
    }

    input::Keys keys_;
    input::Mouse mouse_;

private:
    Input() = default;
};
