#include <iostream>
#include "matrices.hpp"

#include "OpenGL.h"

#include "singleton/Window.hpp"
#include "scene/Menu.hpp"
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

    Scene*  s      = new scene::Menu();
    Window& window = Window::Instance();

    while (!window.ShouldClose() && !Input::Instance().IsOn(GLFW_KEY_ESCAPE)) {
        double delta = UpdateTimer();
        Scene* next  = s->Update(delta);

        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        s->Draw();

        // Switch scenes if needed
        if (s != next) {
            if (next == nullptr) {
                break;
            }

            delete s;
            s = next;
        }

        glfwSwapBuffers(window.GetWindow());
        glfwPollEvents();
    }
}
