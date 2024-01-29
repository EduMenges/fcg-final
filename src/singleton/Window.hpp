#pragma once

#include <variant>
#include "string_view"
#include "Camera.hpp"
#include "singleton/Renderer.hpp"

#include "OpenGL.h"

class Window {
   public:
    static constexpr std::string_view kGameName = "FooBar";

    static Window& Instance() {
        static Window instance;
        return instance;
    }

    [[nodiscard]] GLFWwindow* GetWindow() const { return window_; }

    void FrameBufferSizeCallback(int width, int height);

    [[nodiscard]] bool ShouldClose() { return (glfwWindowShouldClose(window_) == GLFW_TRUE); }

   private:
    Window();

    int width_  = 800;
    int height_ = 800;

    GLFWwindow* window_ = nullptr;
};
