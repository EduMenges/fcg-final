#include "Input.hpp"
#include "singleton/Window.hpp"

void Input::UpdateMouse() {
    double xpos;
    double ypos;
    glfwGetCursorPos(Window::Instance().GetWindow(), &xpos, &ypos);
    mouse_.SetPos(xpos, ypos);
}
