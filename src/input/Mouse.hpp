#pragma once

#include "Action.hpp"

namespace input {
struct Mouse {
    double x = 0.0;
    double y = 0.0;

    bool M1 = false;
    bool M2 = false;

    void TakeAction(int button, Action action) {
        bool active;

        switch (action) {
            case Action::kRelease:
                active = false;
                break;
            case Action::kPress:
                active = true;
                break;
            case Action::kRepeat:
                return;
        }

        if (button == GLFW_MOUSE_BUTTON_LEFT)
        {
            M1 = active;
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            M2 = active;
        }
    }
};
}
