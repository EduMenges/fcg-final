#include "Window.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <utility>

#include "fmt/core.h"
#include "Scene.hpp"
#include "scene/Menu.hpp"

void Window::Start() {}

Window::Window()
    : window_(glfwCreateWindow(width_, height_, kGameName.data(), nullptr, nullptr)), camera_(FreeCamera()) {
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

    glfwSetWindowSize(window_, width_, height_);  // Definição de screenRatio.

    glfwMakeContextCurrent(window_);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

void Window::CursorPosCallback(double xpos, double ypos) {
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

float Window::Update() {
    timer_.previous = std::exchange(timer_.current, glfwGetTime());
    return static_cast<float>(timer_.current - timer_.previous);
}

bool Window::ShouldClose() { return (glfwWindowShouldClose(window_) == GLFW_TRUE); }

void Window::Loop() {
    Scene* s = new scene::Menu();

    while (!ShouldClose()) {
        float  dt   = Update();
        Scene* next = s->Update(dt);

        glClearColor(255, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Switch scenes if needed
        if (s != next) {
            if (next == nullptr) {
                break;
            }

            delete s;
            s = next;
        }

        glfwSwapBuffers(window_);
        glfwPollEvents();
    }
}
