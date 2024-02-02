#include "Mouse.hpp"

void input::Mouse::TakeAction(int button, input::Action action) {
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

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        M1 = active;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        M2 = active;
    }
}
