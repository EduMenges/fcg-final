#pragma once

#include <variant>
#include "string_view"
#include "Camera.hpp"
#include "Renderer.hpp"

#include "OpenGL.h"

class Window {
public:
    static constexpr std::string_view kGameName = "FooBar";

    static Window &Instance() {
        static Window instance;
        return instance;
    }

    GLFWwindow *GetWindow() const {
        return window_;
    }

    void FrameBufferSizeCallback(int width, int height) {
        glViewport(0, 0, width, height);
        height_ = height;
        width_ = width;
    }

    [[nodiscard]] bool ShouldClose() { return (glfwWindowShouldClose(window_) == GLFW_TRUE); }

private:
    struct Timer {
        double current = 0;
        double previous = 0;
    };

    Window();

    int width_ = 800;
    int height_ = 600;

    GLFWwindow *window_ = nullptr;
    std::variant<FreeCamera, LookAtCamera> camera_;
};
