#include "Input.hpp"
#include "Window.hpp"

void Input::Init() {
    InitSingleton();

    glfwSetKeyCallback(Window::GetMut().GetWindow(), [](GLFWwindow* window, int key, int scancode, int action, int mode) {
        GetMut().keys_.TakeAction(key, static_cast<input::Action>(action));
    });

    glfwSetMouseButtonCallback(Window::GetMut().GetWindow(), [](GLFWwindow* window, int button, int action, int mods) {
        GetMut().mouse_.TakeAction(button, static_cast<input::Action>(action));
    });

    glfwSetCursorPosCallback(Window::GetMut().GetWindow(), [](GLFWwindow* window, double xpos, double ypos) {
        GetMut().mouse_.SetPos(xpos, ypos);
    });
}
