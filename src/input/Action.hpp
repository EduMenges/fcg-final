#pragma once

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace input {
enum class Action : int {  // NOLINT
    kRelease = GLFW_RELEASE,
    kPress   = GLFW_PRESS,
    kRepeat  = GLFW_REPEAT,
};
}
