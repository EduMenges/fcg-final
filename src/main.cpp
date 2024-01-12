#include <iostream>
#include "matrices.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

#include "Window.hpp"

extern "C" void ErrorCallback(int error_code, const char* description) {
    fmt::println(stderr, "ERROR {}: {}", error_code, description);
}

int main() {
    if (glfwInit() == GLFW_FALSE) {
        fmt::println(stderr, "ERROR: glfwInit() failed.") ;
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Window window;
    window.Start();
}
