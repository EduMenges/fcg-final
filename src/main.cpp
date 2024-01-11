#include <iostream>
#include "matrices.hpp"
#include "SceneObject.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Window.hpp"

extern "C" void ErrorCallback(int error_code, const char* description) {
    fmt::println(stderr, "ERROR {}: {}", error_code, description);
}

int main() {
    int success = glfwInit();
    if (success == GLFW_FALSE) {
        fmt::println(stderr, "ERROR: glfwInit() failed.") ;
        return EXIT_FAILURE;
    }

    if (glfwSetErrorCallback(ErrorCallback) == nullptr) {
        fmt::println(stderr, "ERROR: when setting error callback.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window;
    window.Start();
}
