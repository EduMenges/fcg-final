#pragma once

#include "OpenGL.h"

namespace input {
enum class Action : int {  // NOLINT
    kRelease = GLFW_RELEASE,
    kPress   = GLFW_PRESS,
    kRepeat  = GLFW_REPEAT,
};
}
