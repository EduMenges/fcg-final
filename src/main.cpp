#include <iostream>
#include "matrices.hpp"

#include "OpenGL.h"

#include "Window.hpp"
#include "scene/Menu.hpp"
#include "Input.hpp"

extern "C" void ErrorCallback(int error_code, const char* description) {
    fmt::println(stderr, "ERROR {}: {}", error_code, description);
}

/**
 * Updates internal timer between cycles.
 * @return How much time elapsed between this and last cycle.
 */
static double UpdateTimer(){
    static double last_timestamp = 0.0F;
    static double current_timestamp = 0.0F;

    last_timestamp = std::exchange(current_timestamp, glfwGetTime());
    return current_timestamp - last_timestamp;
}

int main() {
    if (glfwInit() == GLFW_FALSE) {
        fmt::println(stderr, "ERROR: glfwInit() failed.");
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(ErrorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    Scene* s = new scene::Menu();
    Window&  game = Window::Instance();

    while (!game.ShouldClose() && !Input::Instance().IsOn(GLFW_KEY_ESCAPE)) {
        double delta = UpdateTimer();
        Scene* next = s->Update(delta);

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

        glfwSwapBuffers(game.GetWindow());
        glfwPollEvents();
    }
}
