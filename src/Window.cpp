#include "Window.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include <utility>

#include "fmt/core.h"
#include "Scene.hpp"
#include "scene/Menu.hpp"

Window::Window()
    : window_(glfwCreateWindow(width_, height_, kGameName.data(), nullptr, nullptr)), camera_(FreeCamera()) {
    if (window_ == nullptr) {
        throw std::runtime_error("glfwCreateWindow() failed");
    }

    glfwSetWindowUserPointer(window_, this);

    glfwSetFramebufferSizeCallback(window_, [](GLFWwindow* window, int width, int height) {
        auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
        self->FrameBufferSizeCallback(width, height);
    });

    glfwSetWindowSize(window_, width_, height_);  // Definição de screenRatio.

    glfwMakeContextCurrent(window_);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
}

float Window::Update() {
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

void Window::Init() {
    InitSingleton();
}
