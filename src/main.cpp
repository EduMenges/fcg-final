#include <iostream>

#include "OpenGL.h"

#include "singleton/Window.hpp"
#include "scene/Game.hpp"
#include "singleton/Input.hpp"

extern "C" void ErrorCallback(int error_code, const char* description) {
    fmt::println(stderr, "ERROR {}: {}", error_code, description);
}

namespace {
void SetCallbacks() {
    GLFWwindow* window = Window::Instance().GetWindow();

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        Window::Instance().FrameBufferSizeCallback(width, height);
    });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mode) {
        Input::Instance().keys_.TakeAction(key, static_cast<input::Action>(action));
    });

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        Input::Instance().mouse_.TakeAction(button, static_cast<input::Action>(action));
    });

    glfwSetCursorPosCallback(
        window, [](GLFWwindow* window, double xpos, double ypos) { Input::Instance().mouse_.SetPos(xpos, ypos); });
}

/**
 * Updates internal timer between cycles.
 * @return How much time elapsed between this and last cycle.
 */
double UpdateTimer() {
    static double last_timestamp    = 0.0F;
    static double current_timestamp = 0.0F;

    last_timestamp = std::exchange(current_timestamp, glfwGetTime());
    return current_timestamp - last_timestamp;
}
}

int main() {
    if (glfwInit() == GLFW_FALSE) {
        fmt::println(stderr, "ERROR: glfwInit() failed.");
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    SetCallbacks();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Window& window = Window::Instance();
    Input&  input  = Input::Instance();
    Scene*  scene  = new scene::Game();

    input.UpdateMouse();

    while (!window.ShouldClose() && !Input::Instance().IsOn(GLFW_KEY_ESCAPE)) {
        glfwPollEvents();
        glfwSwapBuffers(window.GetWindow());

        glClearColor(1.0F, 1.0F, 1.0F, 1.0F);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        double delta = UpdateTimer();
        input.UpdateMouse();

        Scene* next = scene->Update(delta);

        scene->Draw();

        if (scene != next) {
            if (next == nullptr) {
                break;
            }

            delete scene;
            scene = next;
        }

    }
}
