#pragma once

#include "Singleton.hpp"
#include "input/Keys.hpp"
#include "input/Mouse.hpp"

class Input : public Singleton<Input> {
public:
    static void Init();

    Input() = default;

private:
    input::Keys keys_;
    input::Mouse mouse_;
};
