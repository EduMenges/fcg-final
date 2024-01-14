#pragma once

#include <variant>
#include "string_view"
#include "input/Mouse.hpp"
#include "input/Keys.hpp"
#include "Camera.hpp"
#include "renderer/Renderer.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

class Window {
   public:
    static constexpr std::string_view kGameName = "FooBar";

    Window();

    void Start();

    void Loop();

    void KeyCallback(int key, int /*scancode*/, int action, int /*mode*/) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
            glfwSetWindowShouldClose(glfwGetCurrentContext(), GL_TRUE);
        }

        keys_.TakeAction(key, static_cast<input::Action>(action));
    }

    void FrameBufferSizeCallback(int width, int height) {
        glViewport(0, 0, width, height);
        height_ = height;
        width_  = width;
    }

    void MouseButtonCallback(int button, int action, int /*mods*/) {
        mouse_.TakeAction(button, static_cast<input::Action>(action));
    }

    void CursorPosCallback(double xpos, double ypos);

    float Update();

    bool ShouldClose();

   private:
    struct Timer {
        double current  = 0;
        double previous = 0;
    };

    int width_  = 800;
    int height_ = 600;

    GLFWwindow*                            window_ = nullptr;
    std::variant<FreeCamera, LookAtCamera> camera_;
    input::Keys                            keys_;
    input::Mouse                           mouse_{static_cast<double>(width_) / 2, static_cast<double>(height_) / 2};
    Timer timer_;
    //Renderer                               renderer_;
};
