#include "Window.hpp"

#include "fmt/core.h"

Window::Window() : window_(glfwCreateWindow(width_, height_, kGameName.data(), nullptr, nullptr)) {
    if (window_ == nullptr) {
        throw std::runtime_error("glfwCreateWindow() failed");
    }

    glfwSetWindowUserPointer(window_, this);

    glfwSetWindowSize(window_, width_, height_);

    glfwMakeContextCurrent(window_);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

void Window::FrameBufferSizeCallback(int width, int height)  {
    glViewport(0, 0, width, height);
    width_  = width;
    height_ = height;

    Renderer::Instance().SetScreenRatio(static_cast<float>(width_) / static_cast<float>(height_));
}
