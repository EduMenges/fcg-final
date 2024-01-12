#pragma once

#include "string_view"
#include "input/Mouse.hpp"
#include "input/Keys.hpp"
#include "Camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
   public:
    static constexpr std::string_view kGameName = "FooBar";

    Window() : window_(glfwCreateWindow(width_, height_, kGameName.data(), nullptr, nullptr)), camera_(FreeCamera()) {
        if (window_ == nullptr) {
            glfwTerminate();
            throw std::runtime_error("glfwCreateWindow() failed");
        }

        glfwSetWindowUserPointer(window_, this);

        glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
            auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            self->KeyCallback(key, scancode, action, mode);
        });

        glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods) {
            auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            self->MouseButtonCallback(button, action, mods);
        });

        glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xpos, double ypos) {
            auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            self->CursorPosCallback(xpos, ypos);
        });

        glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
            auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
            self->FrameBufferSizeCallback(width, height);
        });

        glfwSetWindowSize(window_, width_, height_); // Definição de screenRatio.

        glfwMakeContextCurrent(window_);

        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    }

    void Start();

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

    void CursorPosCallback(double xpos, double ypos) {
        const double dx = xpos - mouse_.x;
        const double dy = ypos - mouse_.y;

        if (auto* free_camera = std::get_if<FreeCamera>(&camera_)) {
            const double angle_x = dx / (static_cast<double>(width_) / 2) * 2 * std::numbers::pi;
            const double angle_y = dy / (static_cast<double>(height_) / 2) * 2 * std::numbers::pi;

            free_camera->UpdateViewVector(angle_x, angle_y);
            free_camera->UpdateSpheric(angle_x);
        } else {
            auto look_at_camera = std::get<LookAtCamera>(camera_);
            look_at_camera.UpdateSpheric(dx, dy);
        }

        mouse_.x = xpos;
        mouse_.y = ypos;
    }

   private:
    int height_ = 800;
    int width_  = 600;

    GLFWwindow*                            window_ = nullptr;
    std::variant<FreeCamera, LookAtCamera> camera_;
    input::Keys                            keys_;
    input::Mouse                           mouse_{static_cast<double>(width_) / 2, static_cast<double>(height_) / 2};
};
