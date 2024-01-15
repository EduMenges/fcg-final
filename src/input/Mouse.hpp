#pragma once

#include "Action.hpp"

namespace input {
struct Mouse {
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

    void SetPos(double xpos, double ypos) {
        last_x = std::exchange(x, xpos);
        last_y = std::exchange(y, ypos);
    }

    double x = 0.0;
    double y = 0.0;

    double last_x = 0.0;
    double last_y = 0.0;

    bool M1 = false;
    bool M2 = false;

};
}
