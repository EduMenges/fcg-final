#pragma once

#include <variant>
#include "string_view"
#include "Camera.hpp"
#include "renderer/Renderer.hpp"

#include "glad/glad.h"
#include "glfw/glfw3.h"

class Window : public Singleton<Window> {
public:
    static constexpr std::string_view kGameName = "FooBar";

    static void Init();

    Window();

    void Start();

    void Loop();

    void FrameBufferSizeCallback(int width, int height) {
        glViewport(0, 0, width, height);
        height_ = height;
        width_ = width;
    }

    float Update();

    bool ShouldClose();

    GLFWwindow *GetWindow() { return window_; }

private:
    struct Timer {
        double current = 0;
        double previous = 0;
    };

    int width_ = 800;
    int height_ = 600;

    GLFWwindow *window_ = nullptr;
    std::variant<FreeCamera, LookAtCamera> camera_;
};
