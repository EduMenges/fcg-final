#include "Window.hpp"

#include "fmt/core.h"

Window::Window()
    : window_(glfwCreateWindow(width_, height_, kGameName.data(), nullptr, nullptr)), camera_(FreeCamera()) {
    if (window_ == nullptr) {
        throw std::runtime_error("glfwCreateWindow() failed");
    }

    glfwSetWindowSize(window_, width_, height_);  // Definição de screenRatio.

    glfwMakeContextCurrent(window_);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}
